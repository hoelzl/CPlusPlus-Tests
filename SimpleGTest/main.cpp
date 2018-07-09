// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//

#include <iostream>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/systems/cgs/io.hpp>
#include <boost/units/operators.hpp>

using namespace boost::units;
using namespace boost::units::si;
using namespace boost::units::cgs;

bool printLengths()
{
    auto one_meter{ 1.0 * meter };
    auto one_hundred_centimeters{ 100.0 * centimeters};

    std::cout << "1 m = " << one_meter << " = " << one_hundred_centimeters << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    printLengths();
    return 0;
}