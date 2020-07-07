//
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : graph-reader
// @created     : Thursday Jan 16, 2020 06:38:38 -03
//
// BSD 2-Clause License

// Copyright (c) 2020, Ruan Evangelista Formigoni
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <taygete/graph/reader.hpp>
#include <taygete/graph/graph.hpp>

TEST_CASE("Graph verilog reader", "[graph-reader.hpp]")
{

using namespace taygete;

SECTION("Parser")
{
  std::string c17 {
    "module c17 (N1, N2, N3, N6, N7, N22, N23);"
    "input  N1, N2, N3, N6, N7;"
    "output N22, N23;"
    "wire new_N10_, new_N11_, new_N16_, new_N19_;"
    "assign new_N10_ = ~N1 | ~N3;"
    "assign new_N11_ = ~N3 | ~N6;"
    "assign new_N16_ = ~N2 | ~new_N11_;"
    "assign new_N19_ = ~new_N11_ | ~N7;"
    "assign N22 = ~new_N10_ | ~new_N16_;"
    "assign N23 = ~new_N16_ | ~new_N19_;"
    "endmodule"
  };

  // Create empty graph
  graph::Graph<int64_t> g;

  // Create callback to create graph
  auto callback = [&g](auto const& a, auto const& b)
    { g.emplace(std::make_pair(a,b)); };

  // Read file into a stream
  std::stringstream ss; ss << c17;

  // Pass the stream to the graph_reader
  // and subsequently lorina
  graph::reader::Reader reader(ss, callback);

  // Print graph
  auto data {g.data()};

  for( auto [x,y] : data )
  {
    std::cout << x << " -> " << y << std::endl;
  }
}
}
