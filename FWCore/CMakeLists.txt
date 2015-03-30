################################################################################
# Package: FWCore
################################################################################
gaudi_subdir(FWCore v1r0)

# this declaration will not be needed in the future
#COLIN gaudi_depends_on_subdirs(GaudiAlg GaudiKernel albers)
gaudi_depends_on_subdirs(GaudiAlg GaudiKernel)

gaudi_add_library(FWCore
		  src/*.cpp
                  LINK_LIBRARIES GaudiAlgLib GaudiKernel
                  PUBLIC_HEADERS FWCore)
#COLIN                  LINK_LIBRARIES GaudiAlgLib GaudiKernel albers

gaudi_add_module(FWCorePlugins
                 components/*.cpp
                 LINK_LIBRARIES GaudiAlgLib GaudiKernel FWCore)
