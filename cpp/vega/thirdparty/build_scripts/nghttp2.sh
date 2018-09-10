#!/bin/bash

set -e

VERSION=1.33.0

curl -sSfLO https://github.com/nghttp2/nghttp2/releases/download/v"$VERSION"/nghttp2-"$VERSION".tar.gz
tar xf nghttp2-"$VERSION".tar.gz
cd nghttp2-"$VERSION"
./configure --prefix="$THIRDPARTY_BUILD" --enable-shared=no --enable-lib-only
make V=1 install
