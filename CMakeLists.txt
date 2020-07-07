# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Aug 15, 2019 19:10:37 -03
# @description : Taygete - C++ Generic Data-Structures Collection
######################################################################
# BSD 2-Clause License
#
# Copyright (c) 2020, Ruan Evangelista Formigoni
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.1..3.15)

project(
  taygete
  DESCRIPTION "Taygete - C++ Generic Data-Structures"
  LANGUAGES CXX
  )

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# External Libraries
if(NOT range-v3_FOUND)
  find_package(range-v3 REQUIRED)
endif()

if(NOT lorina_FOUND)
  find_package(lorina REQUIRED)
endif()

# Source Files
add_subdirectory(include)

# Tests
add_subdirectory(test)

# Install
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Export targets
install(
  TARGETS taygete
  EXPORT taygete-targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install exported targets
install(EXPORT taygete-targets
  FILE taygete-targets.cmake
  NAMESPACE taygete::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/taygete
)

# Create config file
configure_package_config_file(
  cmake/taygete-config.cmake.in
  taygete-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/taygete
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# Install config file
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/taygete-config.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/taygete
)

# Install headers
install(
  DIRECTORY
    ${PROJECT_SOURCE_DIR}/include/taygete
  DESTINATION
    ${CMAKE_INSTALL_PREFIX}/include
)

# Packaging
set(CPACK_PACKAGE_NAME                taygete)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Taygete - C++ Generic Data-Structures")
set(CPACK_PACKAGE_INSTALL_DIRECTORY   ${CPACK_PACKAGE_NAME})
set(CPACK_GENERATOR                   "DEB"  )
set(CPACK_DEBIAN_PACKAGE_MAINTAINER   "Ruan")
include(CPack)
