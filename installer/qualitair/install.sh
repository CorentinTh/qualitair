#!/usr/bin/env bash

# ---------------------------- <<< configure installation

binDir="/usr/local/bin"
finalBinaryName="qualitair"

# ---------------------------- >>> configuration ends here

currentBinaryName="qualitair"
configDir="$HOME/.qualitair"
dbName="db.sqlite"
configName="config.ini"

echo "> Executable"
echo "  Copying executable to $binDir"
sudo cp -f "assets/$currentBinaryName" "$binDir/$finalBinaryName"

echo

echo "> Assets"
echo "  Creation of the configuration directory $configDir"
mkdir -p "$configDir"

echo
echo "  - Database"

if [[ -f "$configDir/$dbName" ]]
then
    echo "    A database already exists at $configDir/$dbName."

    while true; do
        read -p "    Do you want to overwrite it? [y/n]" yn
        case $yn in
            [Yy]* )
                echo "    - Overwriting $configDir/$dbName"
                cp -f "assets/$dbName" "$configDir/$dbName"
                break;;
            [Nn]* )
                echo "    - Skipping database installation"
                break;;

            * ) echo "    Please answer yes or no.";;
        esac
    done

else
    echo
    echo "    > Copying database to $configDir/$configName"
    cp -f "assets/$dbName" "$configDir/$dbName"
fi

echo
echo "  - Config"

if [[ -f "$configDir/$configName" ]]
then
    echo "    A configuration file already exists at $configDir/$configName."

    while true; do
        read -p "    Do you want to overwrite it? [y/n]" yn
        case $yn in
            [Yy]* )
                echo "    - Overwriting $configDir/$configName"
                cp -f "assets/$configName" "$configDir/$configName"
                break;;
            [Nn]* )
                echo
                echo "    - Skipping config installation"
                break;;

            * ) echo "    Please answer yes or no.";;
        esac
    done

else
    echo
    echo "> Copying empty config to $configDir/$configName"
    cp -f "assets/$configName" "$configDir/$configName"
fi

echo
echo "    > Creating folder $configDir/html-templates"
mkdir -p "$configDir/html-templates"

echo
echo "    > Copying html-templates to $configDir/html-templates"
cp -f assets/html-templates/*.html "$configDir/html-templates"

echo
echo "> Installation done."
echo





