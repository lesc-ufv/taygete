// vim: set ts=2 sw=2 tw=0 et :
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : graph
// @created     : Thursday Aug 15, 2019 18:54:13 -03
// @license     : MIT
// @description : Taygete - C++ Generic Data-Structures Collection
//

#pragma once

#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <set>

namespace taygete::graph
{

template<typename T>
using Nodes = std::multimap<T,T>;
template<typename T>
using Storage = std::unique_ptr<Nodes<T>>;

template<typename T>
class Graph
{
  private:
  // Private Members
    Storage<T> graph;
    Storage<T> graph_rev;
  public:
  // Constructors
    Graph() noexcept;
    Graph(Graph const& src) noexcept;
    Graph(Graph&& src) noexcept;
    Graph(std::initializer_list<std::pair<T,T>> t) noexcept;
  // Public Methods
    // Element Access
    template<typename U>
    std::vector<T> get_predecessors(U&& u) const noexcept;
    template<typename U>
    std::vector<T> get_successors(U&& u) const noexcept;
    template<typename U>
    std::vector<T> get_adjacent(U&& u) const noexcept;
    template<typename U>
    bool exists_edge(U&& u1, U&& u2) const noexcept;
    Nodes<T>& data() noexcept;
    // Capacity
    std::size_t get_node_count() const noexcept;
    // Modifiers
    template<typename U>
    void emplace(U&& u) noexcept;
    template<typename U, typename... Args>
    void emplace(U&& u, Args&&... args) noexcept;
    template<typename U = std::pair<T,T>>
    void erase_edge(U&& u);
};

//
// Constructors
//
template<typename T>
Graph<T>::Graph() noexcept
  : graph( std::make_unique<Nodes<T>>() )
  , graph_rev( std::make_unique<Nodes<T>>() )
{
}

template<typename T>
Graph<T>::Graph(Graph const& src) noexcept
{
  this->graph = std::make_unique<Nodes<T>>();
  *this->graph = *src.graph;
  this->graph_rev = std::make_unique<Nodes<T>>();
  *this->graph_rev = *src.graph_rev;
}
template<typename T>
Graph<T>::Graph(Graph&& src) noexcept
{
  this->graph = std::move(src.graph);
  this->graph_rev = std::move(src.graph_rev);
}

template<typename T>
Graph<T>::Graph(std::initializer_list<std::pair<T,T>> t) noexcept
  : Graph()
{
  std::for_each(t.begin(), t.end(), [&](auto const& node){
    this->emplace(node);
  });
}

//
// Public Methods
//

template<typename T>
template<typename U>
std::vector<T> Graph<T>::get_predecessors(U&& u) const noexcept
{
  auto range_rev { this->graph_rev->equal_range(u) };

  std::vector<T> v;

  std::for_each(range_rev.first, range_rev.second, [&v](auto const& node){
      v.push_back(node.second);
  });

  return v;
}

template<typename T>
template<typename U>
std::vector<T> Graph<T>::get_successors(U&& u) const noexcept
{
  auto range { this->graph->equal_range(u) };

  std::vector<T> v;

  std::for_each(range.first, range.second, [&v](auto const& node){
      v.push_back(node.second);
  });

  return v;
}

template<typename T>
template<typename U>
std::vector<T> Graph<T>::get_adjacent(U&& u) const noexcept
{
  auto range { this->graph->equal_range(u) };
  auto range_rev { this->graph_rev->equal_range(u) };

  std::vector<T> v;

  std::for_each(range.first, range.second, [&v](auto const& node){
      v.push_back(node.second);
  });

  std::for_each(range_rev.first, range_rev.second, [&v](auto const& node){
      v.push_back(node.second);
  });

  return v;
}

template<typename T>
template<typename U>
bool Graph<T>::exists_edge(U&& u1, U&& u2) const noexcept
{
  auto range { this->graph->equal_range(u1) };

  auto search {std::find_if(range.first, range.second,
      [&u2](auto&& e)
      {
        return e.second == u2;
      }
    )
  };

  return search != range.second;
}

template<typename T>
Nodes<T>& Graph<T>::data() noexcept
{
  return *(this->graph);
}

template<typename T>
std::size_t Graph<T>::get_node_count() const noexcept
{
  std::set<T> uniques;

  for(auto it{this->graph->begin()}; it!=this->graph->end(); ++it)
  {
    uniques.insert(it->first);
    uniques.insert(it->second);
  }

  return uniques.size();
}

template<typename T>
template<typename U>
void Graph<T>::emplace(U&& u) noexcept
{
  this->graph_rev->emplace(std::make_pair(u.second,u.first));
  this->graph->emplace(std::forward<U>(u));
}

template<typename T>
template<typename U, typename... Args>
void Graph<T>::emplace(U&& u, Args&&... args) noexcept
{
  this->graph_rev->emplace(std::make_pair(u.second,u.first));
  this->graph->emplace(std::forward<U>(u));
  this->emplace(std::forward<Args>(args)...);
}

template<typename T>
template<typename U>
void Graph<T>::erase_edge(U&& u)
{
  auto rng_g {this->graph->equal_range(u.first)};
  auto search_g =
    std::find_if(rng_g.first,rng_g.second,
      [&u](auto&& v)
      {
        return u.second == v.second;
      }
    );

  auto rng_r {this->graph_rev->equal_range(u.second)};
  auto search_r =
    std::find_if(rng_r.first,rng_r.second,
      [&u](auto&& v)
      {
        return u.first == v.second;
      }
    );

  if( search_g != rng_g.second && search_r != rng_r.second)
  {
    this->graph->erase(search_g);
    this->graph_rev->erase(search_r);
  }
}

} // namespace taygete::graph
