#!/usr/bin/env bash

if [ ! -d "${HOME}/.brew" ]; then
	echo "Installing home brew and required programs.";
	sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
	source ~/.zshrc
	brew install cmake pkg-config
else
	echo "Home brew already installed.";

	if brew ls --versions cmake > /dev/null ; then
		echo "CMake already installed."
	else
		echo "Installing CMake"
		brew install cmake
	fi

	if brew ls --versions pkg-config > /dev/null ; then
		echo "Pkg-Config already installed."
	else
		echo "Installing Pkg-Config"
		brew install pkg-config
	fi
fi

echo "Installing Bomberman"
mkdir build
cd build
cmake ..
make -j 4

RED='\033[0;31m'
NC='\033[0m' # No Color
echo "Run command: \"${RED}cd build; ./Bomberman${NC}\""