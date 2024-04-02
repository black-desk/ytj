cmake_minimum_required(VERSION 3.11.4 FATAL_ERROR)

project(
  ytj
  VERSION 0.1.4
  DESCRIPTION
    "A header only cpp library and a command line tool to convert yaml to json."
  HOMEPAGE_URL "https://github.com/black-desk/ytj"
  LANGUAGES CXX)

function(get_real_target_name output target)
  get_target_property("${output}" "${target}" ALIASED_TARGET)
  if("${output}" STREQUAL "")
    set("${output}" "${target}")
  endif()
  set("${output}"
      ${${output}}
      PARENT_SCOPE)
endfunction()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(PFL)
include(GitSemver)
gitsemver(PROJECT_VERSION)
if(CMAKE_VERSION VERSION_LESS "3.14")
  message(
    STATUS "cmake version ${CMAKE_VERSION} not compatible with CPM.cmake, "
           "CPMFindPackage fallback to simply find_package.")
  # Only function we used in CPM.cmake is CPMFindPackage
  function(CPMFindPackage)
    cmake_parse_arguments(ARG "" "NAME;VERSION;FIND_PACKAGE_ARGUMENTS" "")
    string(REPLACE " " ";" EXTRA_ARGS "${ARG_FIND_PACKAGE_ARGUMENTS}")
    find_package(${ARG_NAME} ${ARG_VERSION} REQUIRED ${EXTRA_ARGS})
  endfunction()
else()
  include(CPM)
endif()

CPMFindPackage(
  NAME nlohmann_json
  VERSION 3.5.0
  URL "https://github.com/nlohmann/json/archive/refs/tags/v3.5.0.tar.gz"
  EXCLUDE_FROM_ALL ON
  OPTIONS "JSON_Install ON" # nlohmann_json is an INTERFACE dependency of ytj
          "JSON_BuildTests OFF")

CPMFindPackage(
  NAME yaml-cpp
  VERSION 0.6.2
  GITHUB_REPOSITORY jbeder/yaml-cpp
  GIT_TAG ab5f925 # NOTE: We need https://github.com/jbeder/yaml-cpp/pull/583
  GIT_PROGRESS ON
  EXCLUDE_FROM_ALL ON
  OPTIONS "YAML_CPP_INSTALL ON" # yaml-cpp is an INTERFACE dependency of ytj
          "YAML_CPP_BUILD_TESTS OFF")

if(NOT TARGET yaml-cpp::yaml-cpp)
  add_library(yaml-cpp::yaml-cpp ALIAS yaml-cpp)
endif()

include(./cmake/PFL.cmake)

pfl_init(AUTO)

# build library ytj
pfl_add_library(
  OUTPUT_NAME
  ytj
  MERGED_HEADER_PLACEMENT
  LIBRARY_TYPE
  HEADER_ONLY
  SOURCES
  src/ytj/ytj.cpp
  src/ytj/ytj.hpp.in
  APPS
  ytj
  TESTS
  ytj-test
  COMPILE_FEATURES
  INTERFACE
  cxx_std_17
  LINK_LIBRARIES
  INTERFACE
  nlohmann_json::nlohmann_json
  yaml-cpp::yaml-cpp)
