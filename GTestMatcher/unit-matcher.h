// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//
# pragma once

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/operators.hpp>
#include <boost/math/special_functions/next.hpp>


#include "gmock/gmock.h"
#include "gmock/gmock-matchers.h"
#include <cmath>
#include <string>
#include <limits>

#include <iostream>



namespace testing {

    constexpr double tolerance{ 2.0 };

    MATCHER_P(UnitsEq, arg2, std::string("two values with units are ") + std::string(negation ? "not " : "") + std::string("nearly equal"))
    {
        // std::cout << "Comparing " << arg << " and " << value << std::endl;

        using arg2_value_type = typename arg2_type::value_type;
        arg2_value_type diff{ std::abs(arg.value() - arg2.value()) };
        return diff < tolerance * std::numeric_limits<arg2_value_type>::epsilon();
    }

    MATCHER_P(UnitsEqUlp, arg2, std::string("two values with units are ") + std::string(negation ? "not " : "") + std::string("nearly equal (< 4ULP)"))
    {
        auto ulp_diff{ std::abs(boost::math::float_distance(arg.value(), arg2.value()))};
        return ulp_diff < 4;
    }
}
