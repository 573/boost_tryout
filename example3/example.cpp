// example6.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"


namespace { // Avoid cluttering the global namespace.
  // A couple of simple C++ functions that we want to expose to Python.
  std::string greet() { return "hello, world"; }
  int square(int number) { return number * number; }
}


using namespace boost::python;

BOOST_PYTHON_MODULE(boost_example)
{
    // Add regular functions to the module.
    def("greet", greet);
    def("square", square);
}

int main() {
}