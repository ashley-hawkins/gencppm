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

find_package(LLVM 17 REQUIRED CONFIG)
include(AddLLVM)
find_package(Clang 17 REQUIRED CONFIG)
add_compile_definitions(${LLVM_DEFINITIONS} ${CLANG_DEFINITIONS})
add_link_options(${LLVM_LDFLAGS} ${CLANG_LDFLAGS})
add_compile_options(${LLVM_CXXFLAGS} ${CLANG_CXXFLAGS})
include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})

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
add_subdirectory(module_shims)

set(_std_modules)
# std is implied on MSVC, for non-MSVC we need a workaround
if (NOT MSVC)
  list(APPEND _std_modules gencppm_std)
endif()

add_library(${PROJECT_NAME}-module)
target_sources(${PROJECT_NAME}-module PUBLIC FILE_SET CXX_MODULES FILES ${MODULE_SOURCES})
target_link_libraries(${PROJECT_NAME}-module PUBLIC ${_std_modules} clang::ast clang::tooling clang::basic clang::frontend clang::lex llvm::support Microsoft.GSL::GSL)
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
