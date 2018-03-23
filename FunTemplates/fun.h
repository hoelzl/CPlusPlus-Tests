#pragma once

#include <cassert>

enum class name
{
    foo,
    bar,
    baz,
    quux
};

template<name N>
int fun();

template<>
int fun<name::baz>()
{
    return 10;
}

template<name N>
int fun(int in_value)
{
    return in_value;
}


template<>
int fun<name::foo>(int in_value)
{
    return in_value + 1;
}

template<>
int fun<name::baz>(int in_value);
