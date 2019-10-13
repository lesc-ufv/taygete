// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : graph
// @created     : Saturday Aug 17, 2019 20:45:20 -03
// @license     : MIT
// @description : Taygete - C++ Generic Data-Structures Collection
//

#include <array>
#include <catch2/catch.hpp>
#include <taygete/graph.hpp>
#include <taygete/graph/example.hpp>

namespace taygete::graph::test
{

template<typename T>
void check_values(T&& t)
{
  auto index{0};
  static std::array<int32_t,8> constexpr res{ 1, 2, 3, 4, 0, 5, 6, 0 };

  for( auto i : { 0,1,2 } )
  {
    auto neighbors { t.get_adjacent(i) };

    std::for_each(neighbors.cbegin(), neighbors.cend(),
      [&index](auto const& adj){
        REQUIRE( adj == res.at(index++) );
      }
    );
  }
}

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

  SECTION("get_node_count method")
  {
    REQUIRE( example::mux_2_1.get_node_count() == 7 );
    REQUIRE( example::gate_xor.get_node_count() == 7 );
    REQUIRE( example::gate_xnor.get_node_count() == 8 );
    REQUIRE( example::adder_full_1_bit.get_node_count() == 12 );
    REQUIRE( example::parity_generator.get_node_count() == 13 );
    REQUIRE( example::parity_checker.get_node_count() == 19 );
    REQUIRE( example::chebyshev.get_node_count() == 19 );
  }

  SECTION("exists_edge method")
  {
    REQUIRE( example::mux_2_1.exists_edge(0,4) );
    REQUIRE( example::mux_2_1.exists_edge(0,3) );
    REQUIRE( example::mux_2_1.exists_edge(1,5) );
    REQUIRE( example::mux_2_1.exists_edge(2,4) );
    REQUIRE( example::mux_2_1.exists_edge(3,5) );
    REQUIRE( example::mux_2_1.exists_edge(4,6) );
    REQUIRE( example::mux_2_1.exists_edge(5,6) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(0,1) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(0,2) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(0,5) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(0,6) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(1,2) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(1,3) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(4,5) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(4,7) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(5,5) );
    REQUIRE_FALSE( example::mux_2_1.exists_edge(5,7) );
  }
}

} // namespace taygete::graph::test
