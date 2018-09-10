#!/bin/bash

set -e

BASE=`pwd`

VERSION=4.24
curl -sSfLO http://dist.schmorp.de/libev/libev-"${VERSION}".tar.gz
tar xf libev-"$VERSION".tar.gz
cd libev-"$VERSION"
./configure --enable-shared=no --prefix="$THIRDPARTY_BUILD"
make V=1 install
