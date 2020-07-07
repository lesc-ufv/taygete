# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Aug 15, 2019 20:20:29 -03
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

if(NOT Catch2_FOUND)
  find_package(Catch2 REQUIRED)
endif()

if(NOT FunctionalPlus_FOUND)
  find_package(FunctionalPlus REQUIRED)
endif()

if( ${PROJECT_NAME}_tests )
  add_executable(${PROJECT_NAME}_tests tests.cpp)
  target_compile_options(${PROJECT_NAME}_tests
    PRIVATE
      -std=c++2a
      # -Wall
      # -Wextra
      # -Wpedantic
      # -O0
      # -Wshadow
      # -fconcepts-diagnostics-depth=2
      # -Weffc++
  )
  target_link_libraries(${PROJECT_NAME}_tests taygete FunctionalPlus::fplus Catch2::Catch2)
endif()
