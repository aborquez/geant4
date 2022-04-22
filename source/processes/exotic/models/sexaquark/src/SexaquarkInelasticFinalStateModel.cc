#include "SexaquarkInelasticFinalStateModel.hh"
#include "G4DynamicParticle.hh"
#include "G4HadFinalState.hh"
#include "G4HadronicParameters.hh"
#include "G4Sexaquark.hh"
#include "G4AntiSexaquark.hh"
#include "G4Lambda.hh"
#include "G4KaonPlus.hh"
#include "G4KaonZeroShort.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


SexaquarkInelasticFinalStateModel::SexaquarkInelasticFinalStateModel( const G4String& name )
  : G4HadronicInteraction( name ), fParticleChange( nullptr ) {
  SetMinEnergy( 0.0 );                                               //***LOOKHERE*** Min energy of this model
  SetMaxEnergy( G4HadronicParameters::Instance()->GetMaxEnergy() );  //***LOOKHERE*** Max energy of this model (by default 100 TeV)
  fParticleChange = new G4HadFinalState;
}


SexaquarkInelasticFinalStateModel::~SexaquarkInelasticFinalStateModel() {
  delete fParticleChange;
}


std::pair< G4double, G4double > SexaquarkInelasticFinalStateModel::GetEnergyMomentumCheckLevels() const {
  // Not important: relax the check of energy-momentum conservation
  return std::pair< G4double, G4double >( DBL_MAX, DBL_MAX );
}


G4bool SexaquarkInelasticFinalStateModel::IsApplicable( const G4HadProjectile& aTrack, G4Nucleus& /* targetNucleus */ ) {
  // Applicable only to sexaquark and anti_sexaquark
  G4bool result = false;
  if ( aTrack.GetDefinition() == G4Sexaquark::Definition()  ||
       aTrack.GetDefinition() == G4AntiSexaquark::Definition() ) {
    result = true;
  }
  return result;
}


G4HadFinalState* SexaquarkInelasticFinalStateModel::ApplyYourself( const G4HadProjectile& primary, G4Nucleus& nucleus ) {
  //             ************************************************
  //             ***LOOKHERE***   METHOD TO BE REFINED !
  //             ************************************************
  // This method is called by G4HadronicProcess::PostStepDoIt with the hadron projectile
  // (i.e. sexaquark or anti_sequarks in our case) along the z-axis (0.0, 0.0, 1.0).
  // The same method G4HadronicProcess::PostStepDoIt takes care at the end of rotating the final states
  // produced by this method (SexaquarkInelasticFinalStateModel::ApplyYourself) to take into account
  // of the real, original direction of the hadron (sexaquark or anti_sexaquark) projectile.
  fParticleChange->Clear();
  fParticleChange->SetStatusChange( stopAndKill );
  G4double timePrimary = primary.GetGlobalTime();
  const G4DynamicParticle aPart( primary.GetDefinition(), primary.Get4Momentum().vect() );
  G4bool hasInteraction = true;

  // Choose the target nucleon in which the projectile interacts:
  // we assume equal probability between proton or neutron
  G4ParticleDefinition* targetNucleonDefinition = G4Neutron::Definition();
  G4int targetResidualZ = nucleus.GetZ_asInt();
  if ( G4UniformRand() < G4double(nucleus.GetZ_asInt())/G4double(nucleus.GetA_asInt()) ) {
    targetNucleonDefinition = G4Proton::Definition();
    targetResidualZ--;
  }

  // Choose the final-state channel.
  // For simplicity, let's assume the following final-state channels:
  // -  for the sexaquark:       no channels available (the projectile keeps going unperturbed)
  // -  for the anti_sexaquark:  anti_sexaquark + neutron -> anti_Lambda + kaon0s
  //                             anti_sexaquark + proton  -> anti_Lambda + kaon+
  G4ParticleDefinition* daughterDefinition_1 = nullptr;
  G4ParticleDefinition* daughterDefinition_2 = nullptr;
  if ( primary.GetDefinition() == G4Sexaquark::Definition() ) {
    hasInteraction = false;  // No interaction because no final-state channel available
  } else if ( primary.GetDefinition() == G4AntiSexaquark::Definition() ) {
    if ( targetNucleonDefinition == G4Proton::Definition() ) {
      // anti_sexaquark + proton -> anti_Lambda + kaon+
      daughterDefinition_1 = G4AntiLambda::Definition();
      daughterDefinition_2 = G4KaonPlus::Definition();
    } else {
      // anti_sexaquark + neutron -> anti_Lambda + kaon0s
      daughterDefinition_1 = G4AntiLambda::Definition();
      daughterDefinition_2 = G4KaonZeroShort::Definition();
    }
  } else {
    G4cerr << "Primary hadron not sexaquark or anti_sexaquark ! " << G4endl;
    hasInteraction = false;
  }

  if ( hasInteraction ) {
    // Consider the center-of-mass system formed by the projectile hadron and the target nucleon.
    // We assume the target nucleon at rest in the Lab frame (i.e. we neglect its Fermi momentum).
    G4LorentzVector projectileMomentum = primary.Get4Momentum();
    G4LorentzVector targetNucleonMomentum( 0.0, 0.0, 0.0, targetNucleonDefinition->GetPDGMass() );
    G4LorentzVector centerOfMassMomentum = projectileMomentum + targetNucleonMomentum;
    G4double sqrtS = std::sqrt( std::max( 0.0, centerOfMassMomentum.mag2() ) );
    G4LorentzRotation toCms( -1.0*centerOfMassMomentum.boostVector() );  // Lorentz transformation from Lab frame to center-of-mass frame
    G4LorentzRotation toLab( toCms.inverse() );  // Lorentz transformation from the center-of-mass frame to Lab frame
    // Treat the system projectile-hadron - target-nucleon as an isotropic decay into two bodies
    G4double daughterMass_1 = daughterDefinition_1->GetPDGMass();
    G4double daughterMass_2 = daughterDefinition_2->GetPDGMass();
    G4double daughterMomentum = DaughterMomentum( sqrtS, daughterMass_1, daughterMass_2 );
    if ( daughterMomentum < 0.0 ) {
      hasInteraction = false;  // Kinematically forbidden
    } else {
      G4double cosTheta = 2.0*G4UniformRand() - 1.0;
      G4double sinTheta = std::sqrt( (1.0 - cosTheta)*(1.0 + cosTheta) );
      G4double phi = CLHEP::twopi * CLHEP::rad * G4UniformRand(); 
      G4ThreeVector direction( sinTheta*std::cos(phi), sinTheta*std::sin(phi), cosTheta );
      G4double daughterEkin_1 = std::sqrt( daughterMomentum*daughterMomentum + daughterMass_1*daughterMass_1 ) - daughterMass_1;
      G4DynamicParticle* daughterParticle_1 = new G4DynamicParticle( daughterDefinition_1, direction, daughterEkin_1, daughterMass_1 );
      G4double daughterEkin_2 = std::sqrt( daughterMomentum*daughterMomentum + daughterMass_2*daughterMass_2 ) - daughterMass_2;
      G4DynamicParticle* daughterParticle_2 = new G4DynamicParticle( daughterDefinition_2, -1.0*direction, daughterEkin_2, daughterMass_2 );      
      // Lorentz transformation of the 4-momentum of the secondaries from the center-of-mass frame to the Lab frame
      daughterParticle_1->Set4Momentum( toLab * daughterParticle_1->Get4Momentum() );
      daughterParticle_2->Set4Momentum( toLab * daughterParticle_2->Get4Momentum() );
      // Create G4HadSecondary objects for the secondaries and add them to fParticleChange
      G4HadSecondary* secondary = new G4HadSecondary( daughterParticle_1 );
      secondary->SetTime( timePrimary );
      fParticleChange->AddSecondary( *secondary );
      secondary = new G4HadSecondary( daughterParticle_2 );
      secondary->SetTime( timePrimary );
      fParticleChange->AddSecondary( *secondary );
    }
  }

  if ( ! hasInteraction ) {
    // In the case that the interaction cold not occur, return the primary hadron unchanged
    fParticleChange->SetStatusChange( isAlive );
    fParticleChange->SetEnergyChange( primary.GetKineticEnergy() );
    fParticleChange->SetMomentumChange( primary.Get4Momentum().vect().unit() );
    return fParticleChange;
  }

  // Simple treatment of the residual nucleus: only the target nucleon which interacted
  // inelastically with the (anti_)sexaquark is removed from the target nucleus;
  // moreover, we assume that the residual nucleus is at rest and without excitation energy.
  if ( nucleus.GetA_asInt() > 1 ) {
    G4ParticleDefinition* residualNucleusDefinition =
      G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon( targetResidualZ, nucleus.GetA_asInt()-1, 0.0 );
    if ( residualNucleusDefinition != nullptr ) {
      G4DynamicParticle* residualNucleus = new G4DynamicParticle( residualNucleusDefinition, G4ThreeVector( 0.0, 0.0, 0.0 ) );
      G4HadSecondary* secondary = new G4HadSecondary( residualNucleus );
      secondary->SetTime( timePrimary );
      fParticleChange->AddSecondary( *secondary );
    }
  }

  PrintOutInformation( primary, nucleus );  //***LOOKHERE***  Comment out if you don't want to debug
  
  return fParticleChange;
}


G4double SexaquarkInelasticFinalStateModel::DaughterMomentum( const G4double mass, const G4double m_a, const G4double m_b ) {
  // Compute the momentum of the two daugthers - of mass m_a and m_b - in the reference frame
  // of the parent particle - of mass 'mass'. Return -1.0 if the decay is kinematically forbidden.
  G4double result = -1.0;
  if ( mass > m_a+m_b  &&  m_a >= 0.0  &&  m_b >= 0.0 ) { 
    G4double value = (mass + m_a + m_b)*(mass + m_a - m_b)*(mass - m_a + m_b)*(mass - m_a - m_b) / (4.0*mass*mass);
    if ( value > 0.0 ) result = std::sqrt( value );
  }
  return result;
}


void SexaquarkInelasticFinalStateModel::PrintOutInformation( const G4HadProjectile& primary, G4Nucleus& nucleus ) {
  // Print out information, for debugging purposes, after each inelastic nuclear interaction
  // of sexaquark or anti_sexaquark. In particular, the energy-momentum conservation,
  // the electric charge conservation, the baryon number conservation, and the
  // strangeness conservation are checked (as difference between the initial state -
  // (anti_)sexaquark projectile + target nucleus - and the final state - all the
  // secondaries produced).
  // The reference frame is the Laboratory frame, and we assume the target nucleus at rest
  // (i.e. we neglect the thermal motion).
  const G4ParticleDefinition* projectileDef = primary.GetDefinition();
  const G4LorentzVector projectileMomentum = primary.Get4Momentum();
  const G4int targetZ = nucleus.GetZ_asInt();
  const G4int targetA = nucleus.GetA_asInt();
  const G4double targetMass = G4ParticleTable::GetParticleTable()->GetIonTable()->GetIonMass( targetZ, targetA );
  const G4LorentzVector targetNucleusMomentum( G4ThreeVector(0.0, 0.0, 0.0), targetMass );
  G4LorentzVector initialMinusFinalMomentum = projectileMomentum + targetNucleusMomentum;
  G4int initialMinusFinalCharge = primary.GetDefinition()->GetPDGCharge() + targetZ;
  G4int initialMinusFinalBaryonNumber = projectileDef->GetBaryonNumber() + targetA;
  // For the strangeness, the following line is correct for all particles, but not for
  // sexaquark and anti_sexaquark, which needs an ad-hoc treatment - see below.
  G4int initialMinusFinalStrangeness = projectileDef->GetAntiQuarkContent(3) - projectileDef->GetQuarkContent(3);
  if ( projectileDef == G4Sexaquark::Definition() ) {
    initialMinusFinalStrangeness = -2;
  } else if ( projectileDef == G4AntiSexaquark::Definition() ) {
    initialMinusFinalStrangeness = 2;
  }
  const size_t numberOfSecondaries = fParticleChange->GetNumberOfSecondaries();
  G4cout << " ------------- PrintOutInformation ---------------- " << G4endl
         << " Projectile: " << projectileDef->GetParticleName()
         << "   Ekin [MeV] = " << primary.GetKineticEnergy()
         << "   3-momentum [MeV] = " << primary.Get4Momentum().vect() << G4endl
         << " Target: Z=" << targetZ << "    A=" << targetA << G4endl
         << " -> Number of secondaries = " << numberOfSecondaries << G4endl;
  for ( size_t i = 0; i < numberOfSecondaries; ++i ) {
    if ( fParticleChange->GetSecondary( i ) != nullptr ) {
      const G4DynamicParticle* secondaryDP = fParticleChange->GetSecondary( i )->GetParticle();
      if ( secondaryDP == nullptr ) break;
      const G4ParticleDefinition* secondaryDef = secondaryDP->GetDefinition();
      if ( secondaryDef == nullptr ) break;
      G4cout << "\t Secondary i=" << i << "  " << secondaryDef->GetParticleName()
             << "   Ekin [MeV] = " << secondaryDP->GetKineticEnergy()
	     << "   3-momentum [MeV] = " << secondaryDP->GetMomentum()
	     << G4endl;
      initialMinusFinalMomentum -= secondaryDP->Get4Momentum();
      initialMinusFinalCharge -= secondaryDef->GetPDGCharge();
      initialMinusFinalBaryonNumber -= secondaryDef->GetBaryonNumber();
      initialMinusFinalStrangeness -= ( secondaryDef->GetAntiQuarkContent(3) - secondaryDef->GetQuarkContent(3) );
    }
  }
  G4cout << " Momentum balance [MeV] : initial - final = " << initialMinusFinalMomentum << G4endl
         << " Charge balance         : initial - final = " << initialMinusFinalCharge << G4endl
         << " Baryon number balance  : initial - final = " << initialMinusFinalBaryonNumber << G4endl
         << " Strangeness balance    : initial - final = " << initialMinusFinalStrangeness << G4endl
	 << G4endl;
}
