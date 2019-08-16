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

namespace taygete::graph {

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
  // Public Members
  public:
  // Constructors
    Graph();
    Graph(std::initializer_list<std::pair<T,T>> t);
  // Iterators
  // Public Methods
    template<typename U>
    void emplace(U&& u);
    template<typename U, typename... Args>
    void emplace(U&& u, Args&&... args);
    template<typename U>
    std::vector<T> get_adjacent(U&& u);
  // Private Methods
  // Operators
};

//
// Constructors
//
template<typename T>
Graph<T>::Graph()
  : graph( std::make_unique<Nodes<T>>() )
{
}

template<typename T>
Graph<T>::Graph(std::initializer_list<std::pair<T,T>> t)
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
void Graph<T>::emplace(U&& u)
{
  this->graph->emplace(std::forward<U>(u));
}

template<typename T>
template<typename U, typename... Args>
void Graph<T>::emplace(U&& u, Args&&... args)
{
  this->graph->emplace(std::forward<U>(u));
  this->emplace(std::forward<Args>(args)...);
}

template<typename T>
template<typename U>
std::vector<T> Graph<T>::get_adjacent(U&& u)
{
  auto range { this->graph->equal_range(u) };
  std::vector<T> v;
  std::for_each(range.first, range.second, [&v](auto const& pair){
      v.push_back(pair.second);
  });
  return v;
}

} // namespace taygete::graph
