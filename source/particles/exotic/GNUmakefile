# ----------------------------------------------------------
# GNUmakefile for exotic library.  Andrés Bórquez, 21/4/22.
# ----------------------------------------------------------

name := G4exotic

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

include $(G4INSTALL)/config/architecture.gmk

CPPFLAGS += -DG4PARTICLES_ALLOC_EXPORT
CPPFLAGS += -I$(G4BASE)/global/management/include \
            -I$(G4BASE)/global/HEPRandom/include \
            -I$(G4BASE)/global/HEPGeometry/include \
            -I$(G4BASE)/materials/include \
            -I$(G4BASE)/particles/management/include

include $(G4INSTALL)/config/common.gmk
