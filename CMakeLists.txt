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
  DESCRIPTION "Taygete - C++ Generic Data-Structures"
  LANGUAGES CXX
  )

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# External Libraries
find_package(lorina)

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
