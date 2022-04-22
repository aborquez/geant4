# - G4phys_ctor_exotic module build definition

# Define the Geant4 Module.
geant4_add_module(G4phys_ctor_exotic
  PUBLIC_HEADERS
    SexaquarkPhysics.hh
  SOURCES
    SexaquarkPhysics.cc)

geant4_module_link_libraries(G4phys_ctor_exotic
  PUBLIC
    G4globman
    G4hadronic_mgt
    G4exotic_xsect
    G4run
  PRIVATE
    G4baryons
    G4had_fission
    G4had_par_hp
    G4had_preequ_exciton
    G4had_string_diff
    G4had_string_frag
    G4had_theo_max
    G4hadronic_bert_cascade
    G4hadronic_binary
    G4hadronic_deex_photon_evaporation
    G4hadronic_proc
    G4hadronic_util
    G4ions
    G4exotic
    G4exotic_sexaquark
    G4mesons
    G4partman
    G4phys_builders
    G4phys_ctor_factory
    G4physlist_util
    G4procman
    G4shortlived)
