#ifndef SexaquarkPhysics_h
#define SexaquarkPhysics_h 1

#include "G4VPhysicsConstructor.hh"

class G4Sexaquark;
class G4AntiSexaquark;


class SexaquarkPhysics : public G4VPhysicsConstructor {
  // Physics constructor for the hadronic inelastic interaction of sexaquark and anti_sexaquark.
  // It can be used on top of reference physics list (e.g. FTFP_BERT).
  public:
    SexaquarkPhysics( const G4String& nam = "Sexaquark Physics" );
    ~SexaquarkPhysics();
    SexaquarkPhysics & operator=( const SexaquarkPhysics &right ) = delete;
    SexaquarkPhysics( const SexaquarkPhysics& ) = delete;
    virtual void ConstructParticle() override;
    virtual void ConstructProcess() override;
  private:
    G4Sexaquark* fParticle;
    G4AntiSexaquark* fAntiParticle;
};


#endif
