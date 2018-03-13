//
// Created by tc on 2018-03-13.
//

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/systems/cgs/io.hpp>
#include <boost/units/operators.hpp>
#include "gmock/gmock.h"

using namespace boost::units;
using namespace boost::units::si;
using boost::units::cgs::centimeters;

using ::testing::Eq;

TEST(LengthTest, Unitless)
{
    EXPECT_THAT(1, Eq(1));
}

TEST(LengthTest, MetersOnly)
{
    EXPECT_THAT(1.0 * meter, Eq(1.0 * meter));
    EXPECT_TRUE(false) << "1 m = " << 2.0 * meter;
}

TEST(LengthTest, MetersAndCentimeters)
{
    auto one_meter{ 1.0 * meter};
    auto one_hundred_centimeters{ 100.0 * centimeters };
    // EXPECT_THAT(one_meter, Eq(one_hundred_centimeters));
    EXPECT_THAT(one_meter, Eq(static_cast<decltype(one_meter)>(one_hundred_centimeters)));
}