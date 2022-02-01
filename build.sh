#!/bin/bash
set -exo pipefail

CXX=${CXX:-clang++-10}

pushd valijson
git fetch --tags
VERSION=$(git describe --tags | tr -d '\n')
popd

mkdir -p bin
$CXX -Wall -std=c++17 \
    -I valijson/include -I nlohmann/single_include \
    -DVALIJSON_VERSION="\"$VERSION\"" \
    src/main.cpp \
    -o bin/main
