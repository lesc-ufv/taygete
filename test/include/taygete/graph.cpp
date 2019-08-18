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
  static std::array<int32_t,8> constexpr res{ 2, 3, 4, 5, 1, 6, 7, 1 };

  for( auto i : { 1,2,3 } )
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

    p a{1,2}, b{1,3}, c{2,4}, d{2,5}, e{3,6}, f{3,7};
    Graph<int32_t> graph1;
    Graph<int32_t> graph2{ a, b, c, d, e, f };
    Graph<int32_t> graph3{ p(1,2),p(1,3),p(2,4),p(2,5),p(3,6),p(3,7) };
    Graph<int32_t> graph4{ {1,2},{1,3},{2,4},{2,5},{3,6},{3,7} };
    check_values(graph2);
    check_values(graph3);
    check_values(graph4);
  }
}

} // namespace taygete::graph::test
