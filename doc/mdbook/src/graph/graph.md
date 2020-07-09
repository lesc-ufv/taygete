# Graph

<!-- toc -->

## Interface

```cpp
template<typename T>
class Graph;
```

## Constraints

<!-- TODO -->

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
