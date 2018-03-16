//
// Created by tc on 3/16/18.
//
# pragma once

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/operators.hpp>
#include "gmock/gmock.h"
#include "gmock/gmock-matchers.h"
#include <cmath>
#include <string>
#include <limits>

#include <iostream>

namespace testing {

    constexpr double tolerance{ 2.0 };

    MATCHER_P(UnitsEq, arg2, std::string("Checks if two values with units are") + std::string(negation ? " not " : "") + std::string("nearly equal"))
    {
        // std::cout << "Comparing " << arg << " and " << value << std::endl;

        using arg_value_type = typename arg2_type::value_type;
        arg_value_type diff{ std::abs(arg.value() - arg2.value()) };
        return diff < tolerance * std::numeric_limits<arg_value_type>::epsilon();
    }
}
