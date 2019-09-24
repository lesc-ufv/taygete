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

#include <map>
#include <memory>
#include <functional>

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
    Graph(std::initializer_list<std::pair<T,T>> t) noexcept;
  // Public Methods
    // Element Access
    template<typename U>
    std::vector<T> get_adjacent(U&& u) const noexcept;
    Nodes<T> data() const noexcept;
    // Capacity
    T get_node_count() const noexcept;
    // Modifiers
    template<typename U>
    void emplace(U&& u) noexcept;
    template<typename U, typename... Args>
    void emplace(U&& u, Args&&... args) noexcept;
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
std::vector<T> Graph<T>::get_adjacent(U&& u) const noexcept
{
  auto range     { this->graph->equal_range(u)     };
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
Nodes<T> Graph<T>::data() const noexcept
{
  return *(this->graph);
}

template<typename T>
T Graph<T>::get_node_count() const noexcept
{
  return  (this->graph->rbegin()->first > this->graph_rev->rbegin()->first)?
    this->graph->rbegin()->first+1 : this->graph_rev->rbegin()->first+1;
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

} // namespace taygete::graph
