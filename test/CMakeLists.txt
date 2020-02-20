# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Aug 15, 2019 20:20:29 -03
# @license     : MIT
# @description : Taygete - C++ Generic Data-Structures Collection
######################################################################

if( ${PROJECT_NAME}_tests )
  add_executable(${PROJECT_NAME}_tests tests.cpp)
  target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_20)
  target_link_libraries(${PROJECT_NAME}_tests taygete Catch2)
endif()
