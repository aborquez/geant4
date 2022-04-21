# - G4exotic_sexaquark module build definition

# Define the Geant4 Module.
geant4_add_module(G4exotic_sexaquark
  PUBLIC_HEADERS
    SexaquarkInelasticFinalStateModel.hh
  SOURCES
    SexaquarkInelasticFinalStateModel.cc)

geant4_module_link_libraries(G4exotic_sexaquark
  PUBLIC
    G4globman
    G4hadronic_inclxx_utils
    G4hadronic_mgt
    G4hadronic_util
  PRIVATE
    G4heprandom
    G4partman
    G4baryons
    G4bosons
    G4exotic
    G4had_par_hp
    G4heprandom
    G4leptons
    G4materials
    G4track)
