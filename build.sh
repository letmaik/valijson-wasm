#!/bin/bash
set -ex

CXX=${CXX:-clang++-10}

mkdir -p bin
$CXX -Wall -std=c++17 -I valijson/include -I nlohmann/single_include src/main.cpp -o bin/main
