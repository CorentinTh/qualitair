#!/usr/bin/env bash

# Creation of make build directories
mkdir -p cmake-build-debug

cd cmake-build-debug

# Building all targets

if [ -z "$1" ]
  then
    echo "-> No argument supplied: building all targets."
    cmake ../
  else
    echo "-> Building target $1"
    cmake --target $1 ../
fi

make