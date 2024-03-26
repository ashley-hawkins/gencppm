# SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
# SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
#
# SPDX-License-Identifier: LGPL-3.0-only

cmake_minimum_required(VERSION 3.28)
project(gencppm VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
include(CheckIPOSupported)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(WARNING "Please be aware that only compiling with Clang is supported. If you wish to proceed without using Clang as the compiler, please set gencppm_CLANG_VERSION_MAJOR_MINOR manually to a version of libclang (e.g. 18.1) that the tool will be built with, but be aware that if you are building the software with a compiler different to the version of libclang that gencppm was compiled against, the generated glue may be incompatible, as the preprocessor will have been run as if by Clang rather than by the compiler you would be using.")
else()
  if(NOT DEFINED gencppm_CLANG_VERSION_MAJOR_MINOR)
    string(REGEX MATCH "^[0-9]+\.[0-9]+" gencppm_CLANG_VERSION_MAJOR_MINOR ${CMAKE_CXX_COMPILER_VERSION})
  endif()
  if (NOT DEFINED LLVM_ROOT OR NOT DEFINED CLANG_ROOT)
    # Get the path to the compiler
    get_filename_component(CLANG_EXECUTABLE_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    message(STATUS "Found Clang executable directory as ${CLANG_EXECUTABLE_DIR}, using this to get the base directory of the LLVM installation.")
    # Use that to get the path to the root (../)
    get_filename_component(CLANG_INSTALL_PREFIX ${CLANG_EXECUTABLE_DIR} DIRECTORY)

    set(LLVM_ROOT ${CLANG_INSTALL_PREFIX})
    set(CLANG_ROOT ${CLANG_INSTALL_PREFIX})
  endif()
endif()

find_package(LLVM ${gencppm_CLANG_VERSION_MAJOR_MINOR} REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_VERSION} at ${LLVM_DIR}")
include(AddLLVM)
find_package(Clang ${gencppm_CLANG_VERSION_MAJOR_MINOR} REQUIRED CONFIG)
message(STATUS "Found Clang ${Clang_VERSION} at ${CLANG_INSTALL_PREFIX}")
add_compile_definitions(${LLVM_DEFINITIONS} ${CLANG_DEFINITIONS})
add_link_options(${LLVM_LDFLAGS} ${CLANG_LDFLAGS})
add_compile_options(${LLVM_CXXFLAGS} ${CLANG_CXXFLAGS})
include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})

# get major version from LLVM_VERSION
string(REGEX MATCH "[0-9]+" LLVM_VERSION_MAJOR ${LLVM_VERSION})
message(STATUS "LLVM major version: ${LLVM_VERSION_MAJOR}")

message(STATUS "Fetching GSL")
FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG b39e7e4b0987859f5b19ff7686b149c916588658
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(GSL)

set(MODULE_SOURCES
  src/module.cpp
  src/namespace.cpp
  src/ast_visitor.cpp
  src/ast_consumer.cpp
  src/any_of.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE} src/main.cpp)

add_library(${PROJECT_NAME}-module)
target_sources(${PROJECT_NAME}-module PUBLIC FILE_SET CXX_MODULES FILES ${MODULE_SOURCES})
target_link_libraries(${PROJECT_NAME}-module PUBLIC clangTooling Microsoft.GSL::GSL)
target_compile_definitions(${PROJECT_NAME}-module PUBLIC CLANG_DIR="${CLANG_INSTALL_PREFIX}/lib/clang/${LLVM_VERSION_MAJOR}")
llvm_update_compile_flags(${PROJECT_NAME}-module)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-module)
llvm_update_compile_flags(${PROJECT_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(${PROJECT_NAME} PUBLIC -g)
  target_link_options(${PROJECT_NAME} PUBLIC -g)
endif()

if(ipo_supported)
  message(STATUS "IPO / LTO enabled")
  set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(STATUS "IPO / LTO not supported: <${error}>")
endif()

add_custom_target(${PROJECT_NAME}-windows
  WORKING_DIRECTORY ../
  COMMAND ./build-windows.sh
  USES_TERMINAL
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(${PROJECT_SOURCE_DIR}/cmake/gencppm.cmake)
