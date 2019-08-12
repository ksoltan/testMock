# Tests
The test folder was separated from src/ to maintain independent compilation for local build and a Particle. Also, the Particle compilation probably doens't need the tests.

Contains:
include/ - unit testing and mock framework headers (catch, fakeit)
          Add Particle functionality mocks (such as String, Publish, etc) to include/Particle.h
          If you define a fake library class, initialize it in test/main.cpp
unit/ - unit tests

## Running Tests:
From test/ folder:
$ make TEST=true && ./build/allTests

The TEST macro specifies which main function to build, and whether to compile test files. If not set, it will compile for a local build.

## Running Local Build:
From test/ folder:
$ make && ./build/main

The Makefile is a slight mess. Consider changing to Bazel in the future.
