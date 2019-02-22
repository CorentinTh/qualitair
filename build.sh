#!/usr/bin/env bash

# Creation of make build directories
mkdir -p cmake-build-debug

cd cmake-build-debug

# Building all targets

if [ -z "$1" ]
  then
    echo "-> No argument supplied: building all targets."
    cmake ../ -DBUILD_TESTING=OFF -DBUILD_TESTS=OFF
  else
    echo "-> Building target $1"
    cmake --target "$1" ../ -DBUILD_TESTING=OFF -DBUILD_TESTS=OFF
fi

make