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


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <utility>
#include <array>
#include <taygete/graph/graph.hpp>
#include <range/v3/all.hpp>
#include <fplus/fplus.hpp>

namespace taygete::graph::test
{

//
// Aliases
//

template <typename T1, typename T2>
using edge = typename std::pair<T1,T2>;
namespace ra = ranges::actions;
namespace fp = fplus;

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

TEST_CASE("taygete::graph::graph")
{
  auto require = []<typename T>(T&& t){ REQUIRE(std::forward<T>(t)); };
  auto require_false = []<typename T>(T&& t){ REQUIRE_FALSE(std::forward<T>(t)); };

  auto fold_requires = [&]<typename... T>(T&&... t)
  {
    (require(std::forward<T>(t)), ...);
  }; // lambda: fold_requires

  using namespace taygete::graph;

  SUBCASE("taygete::graph::graph::constructors")
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
  } // SUBCASE: "taygete::graph::graph::constructors"

  Graph<int32_t> g
  {
    {1,5},{1,4},{2,5},{2,4},{3,5},{3,6},
    {4,7},{5,7},{6,8},{7,9},{8,9},{9,10},
  };

  SUBCASE("taygete::graph::graph::successors")
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
  } // SUBCASE: "taygete::graph::graph::successors"

  SUBCASE("taygete::graph::graph::predecessors")
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
  } // SUBCASE: "taygete::graph::graph::predecessors"

  SUBCASE("taygete::graph::graph::neighbors")
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
  } // SUBCASE: "taygete::graph::graph::neighbors"

  SUBCASE("taygete::graph::graph::adjacent")
  {
    fold_requires(
      g.adjacent(1,5), g.adjacent(1,4), g.adjacent(2,5), g.adjacent(2,4),
      g.adjacent(3,5), g.adjacent(3,6), g.adjacent(4,7), g.adjacent(5,7),
      g.adjacent(6,8), g.adjacent(7,9), g.adjacent(8,9), g.adjacent(9,10)
    );
  } // SUBCASE: "taygete::graph::graph::adjacent"

  SUBCASE("taygete::graph::graph::vertices_count")
  {
    REQUIRE(g.vertices_count() == 10);
  } // SUBCASE: "taygete::graph::graph::vertices_count"

  SUBCASE("taygete::graph::graph::edges_count")
  {
    REQUIRE(g.edges_count() ==  12);
  } // SUBCASE: "taygete::graph::graph::edges_count"

  SUBCASE("taygete::graph::graph::emplace")
  {
    Graph<int32_t> g;

    g.emplace(edge(1,2),edge(1,3),edge(2,5),edge(2,3));

    REQUIRE(g.adjacent(1,2));
    REQUIRE(g.adjacent(1,3));
    REQUIRE(g.adjacent(2,5));
    REQUIRE(g.adjacent(2,3));

    REQUIRE_FALSE(g.adjacent(2,1));
    REQUIRE_FALSE(g.adjacent(3,1));
    REQUIRE_FALSE(g.adjacent(5,2));
    REQUIRE_FALSE(g.adjacent(3,2));
  } // SUBCASE: "taygete::graph::graph::emplace"

  SUBCASE("taygete::graph::graph::erase")
  {
    auto fold_erase = [&]<typename... T>(T&&... t) -> void
    { (g.erase(std::forward<T>(t)),...); };

    fold_erase(edge(1,5),edge(5,7),edge(6,8),edge(4,7));

    auto fold_has_adjacency = [&]<typename... T>(T... t) -> void
    { (require_false(g.adjacent(t.first, t.second)),...); };

    fold_has_adjacency(edge(1,5),edge(5,7),edge(6,8),edge(4,7));

    fold_requires(
      g.adjacent(1,4), g.adjacent(2,5), g.adjacent(2,4),
      g.adjacent(3,5), g.adjacent(3,6), g.adjacent(7,9),
      g.adjacent(8,9), g.adjacent(9,10)
    );

  } // SUBCASE: "taygete::graph::graph::erase"
} // TEST_CASE: "taygete::graph::graph"

} // namespace taygete::graph::test
