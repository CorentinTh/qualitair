#!/usr/bin/env bash

dir='cmake-build-debug'

# Creation of make build directories
mkdir -p ${dir}

# Building all targets

if [ -z "$1" ]
  then
    echo "-> No argument supplied: building all targets."
    cmake --build ${dir} -- -j 4
  else
    echo "-> Building target $1"
    cmake --build ${dir} --target $1 -- -j 4
fi