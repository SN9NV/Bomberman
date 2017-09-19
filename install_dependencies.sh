#!/usr/bin/env bash

mkdir build
cd build
cmake -D NANOGUI_BUILD_PYTHON=OFF ..
make -j 4
