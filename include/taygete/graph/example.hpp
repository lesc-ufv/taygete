// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : example
// @created     : Sunday Aug 25, 2019 14:35:24 -03
// @license     : MIT
// @description : Taygete - C++ Generic Data-Structures Collection
//

#pragma once
#include <taygete/graph.hpp>

namespace taygete::graph::example
{
  // Example circuits for testing
  // Inputs in the bottom and outputs on the top

  static const Graph<int32_t> mux_2_1
  {
    {5,6},
    {3,5},{4,6},
    {0,3},{0,4},{1,5},{2,4},
  };

  static const Graph<int32_t> gate_xor
  {
    {4,6},{5,6},
    {2,5},{3,4},
    {0,2},{0,4},{1,3},{1,5},
  };

  static const Graph<int32_t> gate_xnor
  {
    {6,7},
    {4,6},{5,6},
    {2,5},{3,4},
    {0,2},{0,4},{1,3},{1,5},
  };

  static const Graph<int32_t> adder_full_1_bit
  {
    {8,11},{9,11},
    {7,8},{7,10},
    {6,7},{6,9},
    {4,6},{5,6},
    {3,4},{3,10},
    {0,3},{0,5},{1,3},{1,5},{2,7},{2,9},
  };

  static const Graph<int32_t> parity_generator
  {
    {10,12},{11,12},
    {8,11},{9,10},
    {7,8},{7,10},
    {5,7},{6,7},
    {3,6},{4,5},
    {0,3},{0,5},{1,4},{1,6},{2,9},{2,11},
  };

  static const Graph<int32_t> parity_checker
  {
    {16,18},{17,18},
    {14,17},{15,16},
    {12,14},{12,16},{13,15},{13,17},
    {8,12},{9,12},{10,13},{11,13},
    {4,9},{5,8},{6,11},{7,10},
    {0,4},{0,8},{1,5},{1,9},{2,6},{2,10},{3,7},{3,11},
  };

  static const Graph<int32_t> chebyshev
  {
    {17,18},
    {15,17},{16,17},
    {12,15},{13,16},{14,16},
    {10,12},{10,13},{11,13},
    {7,10},{8,11},{9,11},
    {4,7},{4,8},{5,9},{6,9},
    {2,4},{2,5},{3,5},
    {0,2},{0,3},{1,3},
  };


} // namespace taygete::graph::example
