# - G4exotic module build definition

# Define the Geant4 Module.
geant4_add_module(G4exotic
  PUBLIC_HEADERS
    G4AntiSexaquark.hh
    G4Sexaquark.hh
  SOURCES
    G4AntiSexaquark.cc
    G4Sexaquark.cc)

geant4_module_link_libraries(G4exotic
  PUBLIC
    G4partman
    G4globman)
