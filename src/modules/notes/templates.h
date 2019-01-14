#pragma once

#include <iostream>
#include <type_traits>

/**
 * Creating a variadic function using templates
 */

// Base Case
template<typename T>
bool pair_comparer(T a, T b)
{
    return a == b;
}

// All Odd Sequences Will Fail
template<typename T>
bool pair_comparer(T a)
{
    return false;
}

// Variadic Template
template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args)
{
    return a == b && pair_comparer(args...);
}

/**
 * Creating and accessing variadic data structures using templates
 */

// Variadic Type Definers
template<class... Ts>
struct tuple
{
};

template<class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...>
{
    tuple(T t, Ts... ts)
        : tuple<Ts...>(ts...)
        , tail(t)
    {
    }

    T tail;
};

// Variadic Type Containers
template<size_t, class>
struct elem_type_holder;

template<class T, class... Ts>
struct elem_type_holder<0, tuple<T, Ts...>>
{
    typedef T type;
};

template<size_t k, class T, class... Ts>
struct elem_type_holder<k, tuple<T, Ts...>>
{
    typedef typename elem_type_holder<k - 1, tuple<Ts...>>::type type;
};

// Variadic Type Accessors
template<size_t k, class... Ts>
typename std::enable_if<k == 0, typename elem_type_holder<0, tuple<Ts...>>::type &>::type tuple_get(tuple<Ts...> &t)
{
    return t.tail;
}

template<size_t k, class T, class... Ts>
typename std::enable_if<k != 0, typename elem_type_holder<k, tuple<T, Ts...>>::type &>::type tuple_get(tuple<T, Ts...> &t)
{
    tuple<Ts...> &base = t;
    return tuple_get<k - 1>(base);
}

// Catch All Variadic Function (these prints the contents of STL containers)
template<template<typename, typename...> class ContainerType, typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...> &c)
{
    for (const auto &v : c)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
}

template<typename T, typename U>
std::ostream &operator<<(std::ostream &out, const std::pair<T, U> &p)
{
    out << "[" << p.first << ", " << p.second << "]";
    return out;
}
