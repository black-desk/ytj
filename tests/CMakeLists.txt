find_package(
  Catch2 QUIET)
if(NOT Catch2_FOUND)
  CPMFindPackage(
    NAME Catch2
    VERSION 3.4.0
    GITHUB_REPOSITORY catchorg/Catch2
    GIT_TAG v3.4.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL ON)
  list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
endif()

pfl_add_executable(
  INTERNAL
  SOURCES
  ./src/ytj/to_json.test.cpp
  ./src/ytj/to_yaml.test.cpp
  LINK_LIBRARIES
  PUBLIC
  ytj::ytj
  Catch2::Catch2WithMain)

include(Catch)

# NOTE: add_custom_command cannot use with ALIAS target. Check
# https://gitlab.kitware.com/cmake/cmake/-/merge_requests/9201.
catch_discover_tests(ytj__ytj__tests)
