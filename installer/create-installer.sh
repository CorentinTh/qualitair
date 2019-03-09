#!/usr/bin/env bash

binaryName="qualitair"
binaryPath="../bin/$binaryName"

if [[ ! -f "$binaryPath" ]]
then
	echo "Error: $binaryPath not found. Has it been built ?"
	exit 1
fi

# Remove the binary from the archive
rm -f archive/assets/${binaryName}

# Put the binary into the future archive folder
cp -f ${binaryPath} archive/assets/${binaryName}

# Zipping the content of the archive folder
zip -r ../qualitair.zip qualitair

# Remove the binary from the archive folder
rm -f archive/assets/${binaryName}