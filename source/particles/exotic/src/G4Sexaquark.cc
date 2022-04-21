#include "G4Sexaquark.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


G4Sexaquark* G4Sexaquark::fInstance = nullptr;


G4Sexaquark::G4Sexaquark( const G4String& aName, G4double mass, G4double width, G4double charge,
			  G4int iSpin, G4int iParity, G4int iConjugation, G4int iIsospin,
			  G4int iIsospin3, G4int gParity, const G4String& pType, G4int lepton,
			  G4int baryon, G4int encoding, G4bool stable, G4double lifetime,
			  G4DecayTable* decaytable, G4bool shortlived, const G4String& subType,
			  G4int anti_encoding, G4double magneticMoment )
 : G4ParticleDefinition( aName, mass, width, charge, iSpin, iParity, iConjugation,
			 iIsospin, iIsospin3, gParity, pType, lepton, baryon,
			 encoding, stable, lifetime, decaytable, shortlived, subType,
                         anti_encoding, magneticMoment ) {}

G4Sexaquark::~G4Sexaquark() {}


G4Sexaquark* G4Sexaquark::Definition() {
  if ( fInstance == nullptr ) {
    fInstance = new G4Sexaquark( "sexaquark",      // name
				 1.8*CLHEP::GeV,   // mass   ***LOOKHERE***
				 0.0,              // width
				 0.0,              // charge
				 0,                // iSpin
				 +1,               // iParity
				 +1,               // iConjugation (not sure, but it should not matter)
				 0,                // iIsospin
				 0,                // iIsospin3
				 0,                // gParity
				 "exotic",         // type (string: "lepton", "meson", "baryon", "nucleus", etc.)
				 0,                // lepton number
				 +2,               // baryon number
				 900000020,        // PDG encoding
				 true,             // is stable?
				 -1.0,             // lifetime (< 0 for stable)
				 nullptr,          // pointer to decay table
				 false,            // is shortlived?
				 "",               // subType (string)
				 -900000020,       // PDG code of the anti-particle
				 0.0               // magnetic moment
			       );
    G4cout << "G4Sexaquark is created." << G4endl;
  }
  return fInstance;
}


G4Sexaquark* G4Sexaquark::SexaquarkDefinition() {
  return Definition();
}


G4Sexaquark* G4Sexaquark::Sexaquark() {
  return Definition();
}
