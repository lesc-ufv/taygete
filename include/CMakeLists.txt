# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Aug 15, 2019 19:14:24 -03
# @license     : MIT
# @description : Taygete - C++ Generic Data-Structures Collection
######################################################################

add_library(taygete INTERFACE)
target_include_directories(taygete INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(taygete INTERFACE cxx_std_20)
target_link_libraries(taygete INTERFACE lorina)
