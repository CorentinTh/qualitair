#!/usr/bin/env bash

dir='cmake-build-debug'


if [[ -z "$1" ]]
  then
  echo "Error, missing argument for build.sh"
  exit 1

elif ["$1" == "init"]; then

    mkdir -p ${dir}
    cd ${dir}
    cmake ../ -DBUILD_TESTING=OFF
    cd ..

elif ["$1" == "all"]; then

    echo "--> Building all targets."
    cmake --build ${dir} -- -j 4

else

    echo "--> Building target $1"
    cmake --build ${dir} --target $1 -- -j 4

fi
