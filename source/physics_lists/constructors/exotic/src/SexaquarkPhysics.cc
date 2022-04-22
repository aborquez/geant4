#include "SexaquarkPhysics.hh"
#include "G4Sexaquark.hh"
#include "G4AntiSexaquark.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4Transportation.hh"
#include "G4HadronInelasticProcess.hh"
#include "SexaquarkCrossSection.hh"
#include "SexaquarkInelasticFinalStateModel.hh"
#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"


SexaquarkPhysics::SexaquarkPhysics( const G4String& nam )
  : G4VPhysicsConstructor( nam ), fParticle( nullptr ), fAntiParticle( nullptr ) {
  SetPhysicsType( bUnknown );
}


SexaquarkPhysics::~SexaquarkPhysics() {}


void SexaquarkPhysics::ConstructParticle() {
  if ( fParticle == nullptr )     fParticle = G4Sexaquark::Definition();
  else                            G4Sexaquark::Sexaquark();
  if ( fAntiParticle == nullptr ) fAntiParticle = G4AntiSexaquark::Definition();
  else                            G4AntiSexaquark::AntiSexaquark();
}


void SexaquarkPhysics::ConstructProcess() {
  if ( verboseLevel > 0 ) {
    G4cout << "SexaquarkPhysics::ConstructProcess" << G4endl;
  }
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  // The same cross section object and the same inelastic final-state model object
  // can be used for both sexaquark and anti_sexaquark, but a separate hadronic
  // inelastic process is instantiated for each of them.
  G4HadronInelasticProcess* sexaquarkInelasticProcess = new G4HadronInelasticProcess( "inelastic", fParticle );
  if ( sexaquarkInelasticProcess != nullptr ) {
    sexaquarkInelasticProcess->AddDataSet( new SexaquarkCrossSection );
    sexaquarkInelasticProcess->RegisterMe( new SexaquarkInelasticFinalStateModel );
    ph->RegisterProcess( sexaquarkInelasticProcess, fParticle );
  } else {
    G4cerr << "sexaquarkInelasticProcess is nullptr !" << G4endl;
  }
  G4HadronInelasticProcess* antiSexaquarkInelasticProcess = new G4HadronInelasticProcess( "inelastic", fAntiParticle );
  if ( antiSexaquarkInelasticProcess != nullptr ) {
    antiSexaquarkInelasticProcess->AddDataSet( new SexaquarkCrossSection );
    antiSexaquarkInelasticProcess->RegisterMe( new SexaquarkInelasticFinalStateModel );
    ph->RegisterProcess( antiSexaquarkInelasticProcess, fAntiParticle );
  } else {
    G4cerr << "antiSexaquarkInelasticProcess is nullptr !" << G4endl;
  }
}
