cmake_minimum_required(VERSION 3.2)
project(mbgeom)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/geojsonvt/)

set(TESTS_SOURCE_FILES ${COMMON_SOURCE_FILES} test/geojsonvt_test.cc geojsonvt/geojsonvt_c_api.cc geojsonvt/util.hh geojsonvt/util.cc)

add_executable(tests ${TESTS_SOURCE_FILES})
