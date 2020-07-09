# Graph

<!-- toc -->

## Interface

```cpp
template<Arithmetic T> requires Referenceable<T>
class Graph;
```

## Constraints

The given can be a [fundamental type](https://en.cppreference.com/w/cpp/language/types)
or an arbitrary type which adhere to the `arithmetic` and reference `constraints`.
```cpp
template<typename T>
using Reference = T&;

template<typename T>
using ConstReference = T const&;

template<typename T>
concept Referenceable =
  requires
  {
    typename Reference<T>;
    typename ConstReference<T>;
  };

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept Floating = std::is_floating_point_v<T>;

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
```


## Constructors
Creates an empty graph.
```cpp
template<typename T>
Graph<T>::Graph() noexcept
```

Creates a copy of a source graph.
```cpp
template<typename T>
Graph<T>::Graph(Graph const& src) noexcept
```

Moves the contents of a source graph, and invalidates its contents.
```cpp
Graph(Graph&& src) noexcept;
```

Initializes a graph with a list of edges.
```cpp
Graph(std::initializer_list<std::pair<T,T>> t) noexcept;
```
## Public aliases

### `value_type`
Returns the type of `T`.
```cpp
using value_type = T;
```

### `reference`
Returns a reference to `T`.
```cpp
using reference = T&;
```

### `const_reference`
Returns a constant reference to `T`.
```cpp
using const_reference = T const&;
```
