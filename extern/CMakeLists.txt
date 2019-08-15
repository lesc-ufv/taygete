# vim: set ts=2 sw=2 tw=0 et :
######################################################################
# @company     : Universidade Federal de Viçosa - Florestal
# @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Aug 15, 2019 19:16:44 -03
# @license     : MIT
# @description : Taygete - C++ Generic Data-Structures Collection
######################################################################

include(FetchContent)

# Override to show current download information
function(Fetch args)
  foreach(arg IN LISTS args)
    message("${C_GREEN} * ${C_RESET}Populating ${arg} Library")
    FetchContent_MakeAvailable(${arg})
  endforeach()
endfunction()


# Submodules
FetchContent_Declare(
  catch
  GIT_REPOSITORY git@github.com:catchorg/Catch2.git
  GIT_TAG v2.9.1
)

# Populate Libraries
if(${PROJECT_NAME}_tests)
  Fetch("catch")
endif()
