#ifndef SexaquarkCrossSection_h
#define SexaquarkCrossSection_h 1

#include "G4VCrossSectionDataSet.hh"

class G4DynamicParticle;
class G4ParticleDefinition;
class G4Material;
class G4NeutronElasticXS;


class SexaquarkCrossSection : public G4VCrossSectionDataSet {
  // Inelastic nuclear cross section for sexaquark and anti_sexaquark
  public:
    explicit SexaquarkCrossSection();
    ~SexaquarkCrossSection();
    static const char* Default_Name() { return "SexaquarkCrossSection"; }
    void CrossSectionDescription( std::ostream& ) const;
    SexaquarkCrossSection & operator=( const SexaquarkCrossSection &right ) = delete;
    SexaquarkCrossSection( const SexaquarkCrossSection& ) = delete;

    // Applicable for all elements
    G4bool IsElementApplicable( const G4DynamicParticle* , G4int , const G4Material* ) override;

    // Element cross section: this is the main method of this class
    G4double GetElementCrossSection( const G4DynamicParticle* , G4int , const G4Material* ) override;

    // Empty (it is called at initialization)
    void BuildPhysicsTable( const G4ParticleDefinition& ) override;
  
  private:
    G4NeutronElasticXS* fNeutronElasticXS;
};


#endif
