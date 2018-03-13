SimpleGTest
===========

This example serves to show

- How to set up a `CMakeLists.txt` that includes
  Boost libraries as well as the Google Test framework.
- How to use iostreams with Boost units (the main
  trick is to include `boost/units/systems/si/io.hpp`
  in addition to `si.hpp`.)

The project contains two targets: `SimpleGTest` runs
the program in `main.cpp`, `UnitTest` runs the tests in
`unit-tests.cpp`. One of the three tests fails so that
the output of the `<<` operator applied to a length is
visible.
