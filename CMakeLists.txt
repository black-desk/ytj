cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(
  yt
  VERSION 0.1.0
  DESCRIPTION
    "A header only cpp library and a command line tool to convert yaml to json."
  HOMEPAGE_URL "https://github.com/black-desk/yt"
  LANGUAGES CXX)

option(YT_BUILD_EXAMPLES "Build examples of yt or not." ${PROJECT_IS_TOP_LEVEL})

option(YT_ENABLE_TESTING "Enable test of yt or not." ${PROJECT_IS_TOP_LEVEL})

option(YT_INSTALL "Enable install target or not." ${PROJECT_IS_TOP_LEVEL})

include(./cmake/GitSemver.cmake)

gitsemver(PROJECT_VERSION)

include(./cmake/CPM.cmake)

# use CPMFindPackage and find_package to get dependencies here.

include(./cmake/PFL.cmake)

pfl_init(ENABLE_TESTING ${YT_ENABLE_TESTING} BUILD_EXAMPLES
         ${YT_BUILD_EXAMPLES} INSTALL ${YT_INSTALL})

if(YT_ENABLE_TESTING)
  enable_testing()
endif()

# build library yt
pfl_add_library(
  VERSION
  ${PROJECT_VERSION}
  INS
  ./include/yt/configure.hpp.in
  ./include/yt/hello.hpp
  SOURCES
  ./src/yt/hello.cpp
  APPS
  yt
  COMPILE_FEATURES
  PUBLIC
  cxx_std_17)
