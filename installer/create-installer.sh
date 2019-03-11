#!/usr/bin/env bash

binaryName="qualitair"
binaryPath="../bin/$binaryName"

templatePath="../html-templates/dist"

if [[ ! -f "$binaryPath" ]]
then
	echo "Error: $binaryPath not found. Has it been built ?"
	exit 1
fi

# Remove the binary from the archive
rm -f "qualitair/assets/$binaryName"

# Remove html-template from the archive
rm -rf "qualitair/assets/html-templates"

mkdir -p "qualitair/assets/html-templates"

# Put the binary into the future archive folder
cp -f ${binaryPath} "qualitair/assets/$binaryName"

# Setting html-templates
cp -f ${templatePath}/*.html "qualitair/assets/html-templates"

# Zipping the content of the archive folder
zip -r "../qualitair.zip" "qualitair"

# Remove the binary from the archive folder
rm -f "archive/assets/$binaryName"

