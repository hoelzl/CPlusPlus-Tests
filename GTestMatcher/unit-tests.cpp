// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//

#include <limits>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/systems/cgs/io.hpp>
#include <boost/units/operators.hpp>
#include "gmock/gmock.h"
#include "unit-matcher.h"

using namespace boost::units;
using namespace boost::units::si;
using boost::units::cgs::centimeters;

using ::testing::Not;
using ::testing::Eq;
using ::testing::UnitsEq;
using ::testing::UnitsEqUlp;


TEST(LengthTest, MetersOnly)
{
    EXPECT_THAT(1.0 * meter, UnitsEq(1.0 * meter));
}

TEST(LengthTest, MetersAndCentimeters)
{
    auto one_meter{ 1.0 * meter };
    auto one_hundred_centimeters{ 100.0 * centimeters };
    EXPECT_THAT(one_meter, UnitsEq(static_cast<decltype(one_meter)>(one_hundred_centimeters)));
}

TEST(LengthTest, ApproximateMeters)
{
    EXPECT_THAT(1.0 * meter, UnitsEq((1.0 + std::numeric_limits<double>::epsilon()) * meter));
    EXPECT_THAT(1.0 * meter, Not(UnitsEq(1.01 * meter)));
    EXPECT_THAT(1.0 * meter, Not(UnitsEq(1.1 * meter)));
}


TEST(LengthTestUlp, MetersOnly)
{
    EXPECT_THAT(1.0 * meter, UnitsEqUlp(1.0 * meter));
}

TEST(LengthTestUlp, MetersAndCentimeters)
{
    auto one_meter{ 1.0 * meter };
    auto one_hundred_centimeters{ 100.0 * centimeters };
    EXPECT_THAT(one_meter, UnitsEqUlp(static_cast<decltype(one_meter)>(one_hundred_centimeters)));
}

TEST(LengthTestUlp, ApproximateMeters)
{
    EXPECT_THAT(1.0 * meter, UnitsEqUlp((1.0 + std::numeric_limits<double>::epsilon()) * meter));
    EXPECT_THAT(1.0 * meter, Not(UnitsEqUlp(1.01 * meter)));
    EXPECT_THAT(1.0 * meter, Not(UnitsEqUlp(1.1 * meter)));
}
