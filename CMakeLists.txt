# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Aug 15, 2019 19:10:37 -03
# @license     : MIT
# @description : Taygete - C++ Generic Data-Structures Collection
######################################################################

cmake_minimum_required(VERSION 3.1..3.15)

project(
  taygete
  DESCRIPTION "Taygete - C++ Generic Data-Structures Collection"
  LANGUAGES CXX
  )

# CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(colors)
define_colors()

# External Libraries
add_subdirectory(extern)

# Source Files
add_subdirectory(include)

# Tests
option(${PROJECT_NAME}_tests "Enable Testing Modules" OFF)

if( ${PROJECT_NAME}_tests )
  message(STATUS "${C_BLUE} * ${C_RESET}${PROJECT_NAME} testing enabled")
  add_subdirectory(test)
endif()
