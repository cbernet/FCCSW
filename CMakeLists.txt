CMAKE_MINIMUM_REQUIRED(VERSION 2.8.5)

#---------------------------------------------------------------
# Load macros and functions for Gaudi-based projects
find_package(GaudiProject)
#---------------------------------------------------------------

# set(DEF_INSTALL_CMAKE_DIR cmake)
# set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
#   "Installation directory for CMake files")
# set(CMAKE_PREFIX_PATH $ENV{ALBERS})
# find_package(alberscore)

# Declare project name and version
# Syntax:
#    gaudi_project(this_project this_version
#                  USE dep_project_1 version_1 [project_2 version_2 ...]
#                  [DATA pkg1 [VERSION vers1] [pkg2 ...])
gaudi_project(FCCSW HEAD
              USE Gaudi v25r2)
