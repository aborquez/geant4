# - G4exotic_xsect module build definition

# Define the Geant4 Module.
geant4_add_module(G4exotic_xsect
  PUBLIC_HEADERS
    SexaquarkCrossSection.hh
  SOURCES
    SexaquarkCrossSection.cc)

geant4_module_link_libraries(G4exotic_xsect
  PUBLIC
    G4exotic
    G4baryons
    G4globman
    G4hadronic_util
    G4heprandom
    G4ions
    G4leptons
    G4materials
    G4partman
  PRIVATE
	  G4bosons
	  G4mesons)
