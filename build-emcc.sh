#!/bin/bash
set -exo pipefail

pushd valijson
git fetch --tags
VERSION=$(git describe --tags | tr -d '\n')
popd

mkdir -p dist
emcc \
    -s WASM=1 \
    -s NO_DISABLE_EXCEPTION_CATCHING \
    -s NO_EXIT_RUNTIME=1 \
    -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']" \
    --shell-file src/html_template/shell_minimal.html \
    -Wall -std=c++17 \
    -I valijson/include -I nlohmann/single_include \
    -DVALIJSON_VERSION="\"$VERSION\"" \
    src/main_emcc.cpp \
    -o dist/index.html
