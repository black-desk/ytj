cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(
  ProejctTemplate
  VERSION 0.1.0
  DESCRIPTION "A cpp proejct template"
  HOMEPAGE_URL "https://github.com/black-desk/cpp-template"
  LANGUAGES CXX)

option(PROEJCTTEMPLATE_BUILD_EXAMPLES "Build examples of ocppi or not."
       ${PROJECT_IS_TOP_LEVEL})

option(PROEJCTTEMPLATE_ENABLE_TESTING "Enable test of ocppi or not."
       ${PROJECT_IS_TOP_LEVEL})

option(PROEJCTTEMPLATE_INSTALL "Enable install target or not."
       ${PROJECT_IS_TOP_LEVEL})

include(./cmake/GitSemver.cmake)

gitsemver(PROJECT_VERSION)

include(./cmake/CPM.cmake)

# use CPMFindPackage and find_package to get dependencies here.

include(./cmake/PFL.cmake)

pfl_init(ENABLE_TESTING ${PROEJCTTEMPLATE_ENABLE_TESTING} BUILD_EXAMPLES
         ${PROEJCTTEMPLATE_BUILD_EXAMPLES} INSTALL ${PROEJCTTEMPLATE_INSTALL})

if(PROEJCTTEMPLATE_ENABLE_TESTING)
  enable_testing()
endif()

# build library ProjectTemplate
pfl_add_library(
  INTERNAL
  VERSION
  ${PROJECT_VERSION}
  INS
  ./src/ProjectTemplate/configure.hpp.in
  SOURCES
  ./src/ProjectTemplate/hello.hpp
  ./src/ProjectTemplate/hello.cpp
  APPS
  hello_world
  COMPILE_FEATURES
  PUBLIC
  cxx_std_17)
