# Tests
The test folder was separated from src/ to maintain independent compilation for local build and a Particle. Also, the Particle compilation probably doens't need the tests.

## Contains:
- include/ : Unit testing and mock framework headers (catch, fakeit)
  - Particle functionality mocks (such as String, Publish, etc).
  - If you define a fake library class, include it in Particle.h and initialize it in both test/main.cpp and run/TIK_V0.cpp (or the main run file).
- run/ : main file for local build. The main file in src/ does not compile with g++, and I wasn't able to make it conditionally include certain files and functions.
- unit/ : Unit tests! BDD style used to hopefully make reading easier. Please update if you want to change functionality or add more.

## Running Tests:
From test/ folder:
$ make TEST=true && ./build/allTests

The TEST macro specifies which main function to build, and whether to compile test files. If not set, it will compile for a local build.

## Running Local Build:
From test/ folder:
$ make && ./build/main

The Makefile is a slight mess. Consider changing to Bazel in the future.
