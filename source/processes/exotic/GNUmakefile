# ----------------------------------------------------------------
# GNUmakefile for exotic processes library. A.Bórquez 21-Apr-22.
# ----------------------------------------------------------------

name := G4proc_exotic

SUBDIRS = cross_sections
SUBDIRS += models/sexaquark

SUBLIBS = G4exotic_xsect
SUBLIBS += G4exotic_sexaquark

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

include $(G4INSTALL)/config/globlib.gmk
