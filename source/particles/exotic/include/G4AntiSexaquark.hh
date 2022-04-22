#ifndef G4AntiSexaquark_h
#define G4AntiSexaquark_h 1

#include "G4ParticleDefinition.hh"


class G4AntiSexaquark : public G4ParticleDefinition {
  // Definition of the anti-sexaquark particle (the anti-particle of the
  // the sexaquark particle defined in the class G4Sexaquark).
  // This is not part of the Geant4 distribution, because only existing
  // (i.e. experimental found and officially recognized) particles are
  // included in Geant4.
  public:
    static G4AntiSexaquark* Definition();
    static G4AntiSexaquark* AntiSexaquarkDefinition();
    static G4AntiSexaquark* AntiSexaquark();
  private:
    static G4AntiSexaquark* fInstance;
    G4AntiSexaquark( const G4String& aName, G4double mass, G4double width, G4double charge,
                     G4int iSpin, G4int iParity, G4int iConjugation, G4int iIsospin,
		     G4int iIsospin3, G4int gParity, const G4String& pType, G4int lepton,
		     G4int baryon, G4int encoding, G4bool stable, G4double lifetime,
		     G4DecayTable* decaytable, G4bool shortlived, const G4String& subType,
		     G4int anti_encoding, G4double magneticMoment );
    virtual ~G4AntiSexaquark();
};


#endif
