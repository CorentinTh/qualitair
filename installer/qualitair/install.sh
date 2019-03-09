#!/usr/bin/env bash

# ---------------------------- <<< configure installation

binDir="/usr/local/bin"
finalBinaryName="qualitair"

# ---------------------------- >>> configuration ends here

currentBinaryName="qualitair"
configDir="$HOME/.qualitair"
dbName="db.sqlite"
configName="config.ini"

echo "> Copying executable to $binDir"
sudo cp -f "assets/$currentBinaryName" "$binDir/$finalBinaryName"

echo "> Creation of the configuration directory $configDir"
mkdir "$configDir"

echo "> Copying empty database to $configDir/$dbName"
cp -f "assets/$dbName" "$configDir/$dbName"

echo "> Copying empty config to $configDir/$configName"
cp -f "assets/$configName" "$configDir/$configName"
