// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : graph
// @created     : Saturday Aug 17, 2019 20:45:20 -03
// @description : Taygete - C++ Generic Data-Structures Collection
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


#include <utility>
#include <array>
#include <catch2/catch.hpp>
#include <taygete/graph/graph.hpp>
#include <range/v3/all.hpp>

namespace taygete::graph::test
{

//
// Aliases
//

template <typename T1, typename T2>
using link = typename std::pair<T1,T2>;
namespace ra = ranges::actions;

//
// Helpers
//

template<typename T>
void check_values(T&& t)
{
  auto index{0};
  static std::array<int32_t,8> constexpr res{ 1, 2, 3, 4, 0, 5, 6, 0 };

  for( auto i : { 0,1,2 } )
  {
    auto neighbors { t.neighbors(i) };

    std::for_each(neighbors.cbegin(), neighbors.cend(),
      [&index](auto const& adj){
        REQUIRE( adj == res.at(index++) );
      }
    );
  }
}

//
// Tests
//

TEST_CASE("Graph data structure", "[graph]")
{
  using namespace taygete::graph;

  SECTION("Constructors")
  {
    using p = std::pair<int32_t,int32_t>;

    p a{0,1}, b{0,2}, c{1,3}, d{1,4}, e{2,5}, f{2,6};
    Graph<int32_t> graph1;
    Graph<int32_t> graph2{ a, b, c, d, e, f };
    Graph<int32_t> graph3{ p(0,1),p(0,2),p(1,3),p(1,4),p(2,5),p(2,6) };
    Graph<int32_t> graph4{ {0,1},{0,2},{1,3},{1,4},{2,5},{2,6} };
    check_values(graph2);
    check_values(graph3);
    check_values(graph4);

    // Copy and Move constructors
    Graph<int32_t> graph5{graph1};            // Copy
    Graph<int32_t> graph6{std::move(graph2)}; // Move
  }

  Graph<int32_t> g
  {
    {1,5},{1,4},{2,5},{2,4},{3,5},{3,6},
    {4,7},{5,7},{6,8},{7,9},{8,9},{9,10},
  };

  SECTION("taygete::graph::graph::successors")
  {
    REQUIRE((g.successors(1) | ra::sort) == std::vector<int32_t>{4,5});
    REQUIRE((g.successors(2) | ra::sort) == std::vector<int32_t>{4,5});
    REQUIRE((g.successors(3) | ra::sort) == std::vector<int32_t>{5,6});
    REQUIRE((g.successors(4) | ra::sort) == std::vector<int32_t>{7});
    REQUIRE((g.successors(5) | ra::sort) == std::vector<int32_t>{7});
    REQUIRE((g.successors(6) | ra::sort) == std::vector<int32_t>{8});
    REQUIRE((g.successors(7) | ra::sort) == std::vector<int32_t>{9});
    REQUIRE((g.successors(8) | ra::sort) == std::vector<int32_t>{9});
    REQUIRE((g.successors(9) | ra::sort) == std::vector<int32_t>{10});
    REQUIRE((g.successors(10) | ra::sort) == std::vector<int32_t>{});
  }

  SECTION("taygete::graph::graph::predecessors")
  {
    REQUIRE((g.predecessors(1) | ra::sort) == std::vector<int32_t>{});
    REQUIRE((g.predecessors(2) | ra::sort) == std::vector<int32_t>{});
    REQUIRE((g.predecessors(3) | ra::sort) == std::vector<int32_t>{});
    REQUIRE((g.predecessors(4) | ra::sort) == std::vector<int32_t>{1,2});
    REQUIRE((g.predecessors(5) | ra::sort) == std::vector<int32_t>{1,2,3});
    REQUIRE((g.predecessors(6) | ra::sort) == std::vector<int32_t>{3});
    REQUIRE((g.predecessors(7) | ra::sort) == std::vector<int32_t>{4,5});
    REQUIRE((g.predecessors(8) | ra::sort) == std::vector<int32_t>{6});
    REQUIRE((g.predecessors(9) | ra::sort) == std::vector<int32_t>{7,8});
    REQUIRE((g.predecessors(10) | ra::sort) == std::vector<int32_t>{9});
  }

  SECTION("taygete::graph::graph::neighbors")
  {
    REQUIRE((g.neighbors(1) | ra::sort) == std::vector<int32_t>{4,5});
    REQUIRE((g.neighbors(2) | ra::sort) == std::vector<int32_t>{4,5});
    REQUIRE((g.neighbors(3) | ra::sort) == std::vector<int32_t>{5,6});
    REQUIRE((g.neighbors(4) | ra::sort) == std::vector<int32_t>{1,2,7});
    REQUIRE((g.neighbors(5) | ra::sort) == std::vector<int32_t>{1,2,3,7});
    REQUIRE((g.neighbors(6) | ra::sort) == std::vector<int32_t>{3,8});
    REQUIRE((g.neighbors(7) | ra::sort) == std::vector<int32_t>{4,5,9});
    REQUIRE((g.neighbors(8) | ra::sort) == std::vector<int32_t>{6,9});
    REQUIRE((g.neighbors(9) | ra::sort) == std::vector<int32_t>{7,8,10});
  }

  SECTION("taygete::graph::graph::emplace")
  {
    Graph<int32_t> g;
    g.emplace(
      link(1,2),link(1,3),link(2,5),link(2,3)
    );

    REQUIRE(g.adjacent(1,2));
    REQUIRE(g.adjacent(1,3));
    REQUIRE(g.adjacent(2,5));
    REQUIRE(g.adjacent(2,3));

    REQUIRE_FALSE(g.adjacent(2,1));
    REQUIRE_FALSE(g.adjacent(3,1));
    REQUIRE_FALSE(g.adjacent(5,2));
    REQUIRE_FALSE(g.adjacent(3,2));
  }
}

} // namespace taygete::graph::test
