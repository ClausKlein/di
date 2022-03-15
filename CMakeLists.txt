#
# Copyright (c) 2012-2022 Kris Jusiak (kris at jusiak dot net)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 3.16...3.22)

project(
  DI
  VERSION 1.2.1
  LANGUAGES CXX
)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14 CACHE STRING "Default value for CXX_STANDARD property of targets.")
  option(CMAKE_CXX_STANDARD_REQUIRED "Default value for CXX_STANDARD_REQUIRED property of targets." YES)
  option(CMAKE_CXX_EXTENSIONS "Default value for CXX_EXTENSIONS property of targets." NO)
endif()
if(NOT DEFINED CXX_STANDARD)
  set(CXX_STANDARD ${CMAKE_CXX_STANDARD} CACHE STRING "C++ Standard Version. [14|17|20]")
endif()

add_library(${PROJECT_NAME} INTERFACE)
set(INCLUDE_INSTALL_DIR include/${PROJECT_NAME}-${PROJECT_VERSION}/include)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/extension/include>
  $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>)
# NOTE: this will not exported! set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # XXX set(COMPILER_SPECIFIC_CXX_STANDARD "/std:c++${CXX_STANDARD}")
  # XXX string(REPLACE "20" "latest" COMPILER_SPECIFIC_CXX_STANDARD ${COMPILER_SPECIFIC_CXX_STANDARD})

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_SPECIFIC_CXX_STANDARD} /W3 /EHsc /Zc:__cplusplus")

  # being a cross-platform target, we enforce standards conformance on MSVC
  # TODO: target_compile_options(${PROJECT_NAME} INTERFACE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_TOPLEVEL_PROJECT TRUE)
  option(WarningsAsErrors "Be really pedantic!" YES)
  if(WarningsAsErrors)
    include(cmake/WarningsAsErrors.cmake)
  endif()
else()
  set(IS_TOPLEVEL_PROJECT FALSE)
endif()

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.8.0
)

# Create target Boost::DI and install target
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE Boost
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION ${INCLUDE_INSTALL_DIR}
  COMPATIBILITY SameMajorVersion
)

option(BOOST_DI_OPT_BUILD_TESTS "Build and perform Boost::DI tests" ${IS_TOPLEVEL_PROJECT})
if(BOOST_DI_OPT_BUILD_TESTS)
  enable_testing()
  add_subdirectory(extension/test)
  add_subdirectory(test)
endif()

option(BOOST_DI_OPT_BUILD_EXAMPLES "Build perform Boost::DI examples" ${IS_TOPLEVEL_PROJECT})
if(BOOST_DI_OPT_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()
