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
  }

  SECTION("get_node_count method")
  {
    Graph<int32_t> tree_like{ {0,1},{0,2},{1,3},{1,4},{2,5},{2,6} };

    Graph<int32_t> chebyshev
    {
      {0,2},{0,3},{1,3},
      {2,4},{2,5},{3,5},
      {4,7},{4,8},{5,9},{6,9},
      {7,10},{8,11},{9,11},
      {10,12},{10,13},{11,13},
      {12,15},{13,16},{14,16},
      {15,17},{16,17},
    };

    REQUIRE( chebyshev.get_node_count() == 18 );
    REQUIRE( tree_like.get_node_count() == 7 );
  }
}

} // namespace taygete::graph::test
