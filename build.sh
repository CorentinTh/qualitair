#!/usr/bin/env bash

# Creation of make build directories
mkdir cmake-build-debug
#mkdir tests/unit-tests/cmake-build-debug

cd cmake-build-debug

# Building all targets
cmake ../
make