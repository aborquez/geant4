#ifndef SexaquarkInelasticFinalStateModel_h
#define SexaquarkInelasticFinalStateModel_h 1

#include "G4HadronicInteraction.hh"

class G4HadFinalState;


class SexaquarkInelasticFinalStateModel : public G4HadronicInteraction {
  // Inelastic hadronic final-state model for sexaquark and anti_sexaquark 
  public:
    explicit SexaquarkInelasticFinalStateModel( const G4String& name = "SexaquarkInelasticFinalStateModel" );
  
    ~SexaquarkInelasticFinalStateModel();
    SexaquarkInelasticFinalStateModel( const SexaquarkInelasticFinalStateModel& right ) = delete;
    const SexaquarkInelasticFinalStateModel & operator=( const SexaquarkInelasticFinalStateModel& right ) = delete;
    G4bool operator==( const SexaquarkInelasticFinalStateModel& right ) const = delete;
    G4bool operator!=( const SexaquarkInelasticFinalStateModel& right ) const = delete;

    // This hadron inelastic final-state model should be applicable only for sexaquark and anti_sexaquark 
    G4bool IsApplicable( const G4HadProjectile& aTrack, G4Nucleus& targetNucleus ) override;

    // This is the main method that produces secondaries from the inelastic interaction of
    // sexaquark or anti_sexaquark projectile on a target nucleus
    G4HadFinalState* ApplyYourself( const G4HadProjectile& thePrimary, G4Nucleus& theNucleus ) override;

    std::pair< G4double, G4double > GetEnergyMomentumCheckLevels() const override;
  
  private:
    G4double DaughterMomentum( const G4double m, const G4double m1, const G4double m2 );
    void PrintOutInformation( const G4HadProjectile& primary, G4Nucleus& nucleus );

    G4HadFinalState* fParticleChange;
};


#endif
