// vim: set expandtab fdm=marker ts=2 sw=2 tw=100 et
//
// @company     : Universidade Federal de Viçosa - Florestal
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : graph
// @created     : Thursday Aug 15, 2019 18:54:13 -03
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


#pragma once

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <type_traits>
#include <concepts>
#include <taygete/concepts.hpp>
#include <range/v3/all.hpp>
#include <fplus/fplus.hpp>

// {{{ taygete::graph
namespace taygete::graph
{

// Namespaces {{{
namespace rg = ranges;
namespace ra = ranges::actions;
namespace fp = fplus;
namespace cp = taygete::concepts;
// }}}

// Aliases {{{
template<typename T>
using Vertices = std::multimap<T,T>;
template<typename T>
using Storage = std::unique_ptr<Vertices<T>>;
// }}}

// Graph {{{

template<cp::Arithmetic T> requires cp::Referenceable<T>
class Graph
{
  // Private Members {{{
  private:
    Storage<T> g;
    Storage<T> gr;
  // }}}

  // Public Members {{{
  public:
    using value_type = T;
    using reference = T&;
    using const_reference = T const&;
  // }}}

  // Constructors {{{
  public:
    Graph() noexcept;
    Graph(Graph const& src) noexcept;
    Graph(Graph&& src) noexcept;
    Graph(std::initializer_list<std::pair<T,T>> t) noexcept;
  // }}}

  // Public Methods {{{
    // Element Access {{{
    template<typename U> requires cp::ConvertibleTo<T,U>
    std::vector<T> successors(U u) const noexcept;
    template<typename U> requires cp::ConvertibleTo<T,U>
    std::vector<T> predecessors(U u) const noexcept;
    template<typename U> requires cp::ConvertibleTo<T,U>
    std::vector<T> neighbors(U&& u) const noexcept;
    template<typename U> requires cp::ConvertibleTo<T,U>
    bool adjacent(U&& u1, U&& u2) const noexcept;
    Vertices<T>& data() noexcept;
    // }}}

    // Capacity {{{
    std::size_t vertices_count() const noexcept;
    std::size_t edges_count() const noexcept;
    // }}}

    // Modifiers {{{
    template<typename... U> requires cp::IsPairsOf<T,U...>
    void emplace(U&&... u) noexcept;
    template<typename U = std::pair<T,T>> requires cp::IsPairOf<T,U>
    void erase(U&& u) noexcept;
    // }}}

  // }}}
};

// }}}

// Constructors {{{
template<typename T>
Graph<T>::Graph() noexcept
  : g( std::make_unique<Vertices<T>>() )
  , gr( std::make_unique<Vertices<T>>() )
{
}

template<typename T>
Graph<T>::Graph(Graph const& src) noexcept
{
  this->g = std::make_unique<Vertices<T>>();
  *this->g = *src.g;
  this->gr = std::make_unique<Vertices<T>>();
  *this->gr = *src.gr;
}
template<typename T>
Graph<T>::Graph(Graph&& src) noexcept
{
  this->g = std::move(src.g);
  this->gr = std::move(src.gr);
}

template<typename T>
Graph<T>::Graph(std::initializer_list<std::pair<T,T>> t) noexcept
  : Graph()
{
  rg::for_each(t, [&](auto&& v){this->emplace(v);});
}
/// }}}

// Public Methods {{{

// Element Access {{{
template<typename T>
template<typename U> requires cp::ConvertibleTo<T,U>
std::vector<T> Graph<T>::successors(U u) const noexcept
{
  return fp::get_map_values(fp::map_keep_if([&u](auto k){ return k == u; },*g));
}

template<typename T>
template<typename U> requires cp::ConvertibleTo<T,U>
std::vector<T> Graph<T>::predecessors(U u) const noexcept
{
  return fp::get_map_keys(fp::map_keep_values(std::vector<U>{u},*g));
}

template<typename T>
template<typename U> requires cp::ConvertibleTo<T,U>
std::vector<T> Graph<T>::neighbors(U&& u) const noexcept
{
  return
    fp::append(this->successors(std::forward<U>(u)),this->predecessors(std::forward<U>(u)))
    | ra::unique;
}

template<typename T>
template<typename U> requires cp::ConvertibleTo<T,U>
bool Graph<T>::adjacent(U&& u1, U&& u2) const noexcept
{
  return
    fp::is_elem_of(u2,fp::get_map_values(fp::map_keep_if([&u1](auto k){return k==u1;},*g)));
}

template<typename T>
Vertices<T>& Graph<T>::data() noexcept
{
  return *(this->g);
}
// }}}

// Capacity {{{

template<typename T>
std::size_t Graph<T>::vertices_count() const noexcept
{
  return
    (fp::append(fp::get_map_keys(*g),fp::get_map_values(*g)) | ra::sort | ra::unique).size();
}

template<typename T>
std::size_t Graph<T>::edges_count() const noexcept
{
  return g->size();
}

// }}}

// Modifiers {{{

template<typename T>
template<typename... U> requires cp::IsPairsOf<T,U...>
void Graph<T>::emplace(U&&... u) noexcept
{
  (this->g->emplace(std::forward<U>(u)),...);
  (this->gr->emplace(std::forward<U>(u)),...);
}

template<typename T>
template<typename U> requires cp::IsPairOf<T,U>
void Graph<T>::erase(U&& u) noexcept
{
  auto rng{this->g->equal_range(u.first)};

  for (auto it{rng.first}; it != rng.second; ++it)
  {
    if( u.second == it->second )
    {
      this->g->erase(it);
      break;
    }
  } // for: it != rng.second

  auto rngr {this->gr->equal_range(u.first)};
  for (auto it{rngr.first}; it != rngr.second; ++it)
  {
    if( u.second == it->second )
    {
      this->gr->erase(it);
      break;
    }
  } // for: it != rngr.second
} // function: erase

// }}}

// }}}

} // namespace taygete::graph }}}
