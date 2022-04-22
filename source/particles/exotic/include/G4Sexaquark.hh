#ifndef G4Sexaquark_h
#define G4Sexaquark_h 1

#include "G4ParticleDefinition.hh"


class G4Sexaquark : public G4ParticleDefinition {
  // Definition of the sexaquark particle.
  // This is not part of the Geant4 distribution, because only existing
  // (i.e. experimental found and officially recognized) particles are
  // included in Geant4.
  public:
    static G4Sexaquark* Definition();
    static G4Sexaquark* SexaquarkDefinition();
    static G4Sexaquark* Sexaquark();
  private:
    static G4Sexaquark* fInstance;
    G4Sexaquark( const G4String& aName, G4double mass, G4double width, G4double charge,
		 G4int iSpin, G4int iParity, G4int iConjugation, G4int iIsospin, G4int iIsospin3,
		 G4int gParity, const G4String& pType, G4int lepton, G4int baryon, G4int encoding,
		 G4bool stable, G4double lifetime, G4DecayTable* decaytable, G4bool shortlived,
		 const G4String& subType, G4int anti_encoding, G4double magneticMoment );
    virtual ~G4Sexaquark();
};


#endif
