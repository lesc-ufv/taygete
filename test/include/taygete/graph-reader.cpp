/**
 * @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
 * @file        : graph-reader
 * @created     : Thursday Jan 16, 2020 06:38:38 -03
 */

#include <taygete/graph-reader.hpp>
#include <taygete/graph.hpp>

TEST_CASE("Graph verilog reader", "[graph-reader.hpp]")
{

using namespace taygete;

SECTION("File parsing")
{

  graph::Graph<int64_t> g;

  auto callback = [&g](auto const& a, auto const& b)
    { g.emplace(std::make_pair(a,b)); };

  graph::graph_reader::graph_reader<decltype(callback)>
    reader("adder-1bit.v", callback);

  auto data {g.data()};

  for( auto [x,y] : data )
  {
    std::cout << x << " -> " << y << std::endl;
  }
}

}
