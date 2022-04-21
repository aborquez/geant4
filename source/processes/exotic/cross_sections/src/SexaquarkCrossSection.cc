#include "SexaquarkCrossSection.hh"
#include "G4Sexaquark.hh"
#include "G4AntiSexaquark.hh"
#include "G4Neutron.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh"
#include "G4IsotopeList.hh"
#include "G4NeutronElasticXS.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


SexaquarkCrossSection::SexaquarkCrossSection() : G4VCrossSectionDataSet( Default_Name() ) {
  verboseLevel = 0;
  SetForAllAtomsAndEnergies( true );
  fNeutronElasticXS = new G4NeutronElasticXS; 
}


SexaquarkCrossSection::~SexaquarkCrossSection() {
  delete fNeutronElasticXS;
}


void SexaquarkCrossSection::CrossSectionDescription( std::ostream& outFile ) const {
  outFile << "SexaquarkCrossSection is assumed to be either constant and scaling with the \n";
  outFile << "number of nucleons, or proportional to the neutron elastic cross section.\n";
}


void SexaquarkCrossSection::BuildPhysicsTable( const G4ParticleDefinition& ) {}


G4bool SexaquarkCrossSection::IsElementApplicable( const G4DynamicParticle* , G4int , const G4Material* ) {
  return true;
}


G4double SexaquarkCrossSection::GetElementCrossSection( const G4DynamicParticle* aParticle, G4int aZ, const G4Material* aMaterial ) {
  //     *********************************************
  //     ***LOOKHERE***   METHOD TO BE REFINED !
  //     *********************************************
  // For simplicity, we assume that the sexaquark inelastic cross section is a constant
  // (i.e. not dependent on the kinetic energy of the sexaquark) value per nucleon, and
  // therefore the cross section on a nucleus is proportional to the number of nucleons.
  // For anti_sexaquark, we assume instead that the nuclear cross section is proportional
  // to the neutron elastic cross section on the same nucleus (with the neutron having
  // the same kinetic energy as the anti_sexaquark).
  G4double xs = 0.0;
  G4ParticleDefinition* projectileDef = aParticle->GetDefinition();
  if ( projectileDef != nullptr ) {
    if ( projectileDef == G4Sexaquark::Definition() ) {
      const G4double constantXsecPerNucleon = 1.0*CLHEP::millibarn;  //***LOOKHERE***
      xs = constantXsecPerNucleon * aeff[aZ];  // aeff[aZ] gives the effective number of nucleons (see class G4IsotopeList)
      //G4cout << "SexaquarkCrossSection::GetElementCrossSection=" << xs / CLHEP::millibarn
      //       << " mb - sexaquark projectile on " << aMaterial->GetName() << G4endl;  // For debugging
    } else if ( projectileDef == G4AntiSexaquark::Definition() ) {
      G4DynamicParticle* neutronProxy =
	new G4DynamicParticle( G4Neutron::Definition(), aParticle->GetMomentumDirection(), aParticle->GetKineticEnergy() );
      const G4double scaleFactor = 2.0;  //***LOOKHERE***  Scale factor for the elastic neutron cross section
      xs = scaleFactor * fNeutronElasticXS->GetElementCrossSection( neutronProxy, aZ, aMaterial );
      //G4cout << "SexaquarkCrossSection::GetElementCrossSection=" << xs / CLHEP::millibarn
      //       << " mb - anti_sexaquark projectile on " << aMaterial->GetName() << G4endl;  // For debugging
    } else {
      G4cerr << "ERROR : unexpected projectile particle : " << projectileDef->GetParticleName() << G4endl;
    }
  }
  return xs;
}
