/* vim: set expandtab fdm=marker ts=2 sw=2 tw=100 et :*/
//
// @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
// @file        : concepts
// @created     : sexta jul 10, 2020 03:57:13 -03
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

#include <type_traits>
#include <concepts>

// taygete::concepts {{{

namespace taygete::concepts
{

template<typename T>
using Reference = T&;

template<typename T>
using ConstReference = T const&;

// ConvertibleTo {{{

template<typename T, typename U>
concept ConvertibleTo = std::convertible_to<std::decay_t<T>,std::decay_t<U>>;

// }}}

// Referenciable {{{

template<typename T>
concept Referenceable =
requires
{
  typename Reference<T>;
  typename ConstReference<T>;
};

// }}}

// Integral {{{

template<typename T>
concept Integral = std::is_integral_v<T>;

// }}}

// Floating {{{

template<typename T>
concept Floating = std::is_floating_point_v<T>;

// }}}

// Arithmetic {{{

template<typename T>
concept Arithmetic =
Integral<T>
|| Floating<T>
|| requires(T t)
  {
    { t+t } -> std::same_as<T>;
    { t-t } -> std::same_as<T>;
    { t*t } -> std::same_as<T>;
    { t/t } -> std::same_as<T>;
  };

// }}}

// IsPairOf {{{

template<typename T, typename U>
concept IsPairOf =
requires(U u)
{
  {u.first} -> std::convertible_to<std::decay_t<T>>;
  {u.second} -> std::convertible_to<std::decay_t<T>>;
};

// }}}

// IsPairsOf {{{

template<typename T, typename... U>
concept IsPairsOf =
requires(U... u)
{
  { ((u.first),...) } -> std::convertible_to<std::decay_t<T>>;
  { ((u.second),...) } -> std::convertible_to<std::decay_t<T>>;
};

// }}}


} // namespace taygete::concepts }}}
