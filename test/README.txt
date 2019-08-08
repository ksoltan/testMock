Test folder was separated from src to maintain independent compilation and not including tests in particle compile.

Contains:
include/ - unit testing and mock framework headers (catch, fakeit)
          Add Particle functionality mocks (such as String, Publish, etc) to include/Particle.h
unit/ - unit tests

To run tests, from test/ folder:
$ make && ./build/allTests

The Makefile is a slight mess. Consider changing to bazel in the future.
