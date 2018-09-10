#!/bin/bash

set -e

BASEDIR="${PWD}"
BUILD_LOG="${BASEDIR}/build.log"

export THIRDPARTY_DEPS="${BASEDIR}"
export THIRDPARTY_BUILD="${BASEDIR}/thirdparty_build"

set -o pipefail
for r in "$@"
do
    make -j 3 "${THIRDPARTY_DEPS}/${r}.dep" 2>&1 | tee "${BUILD_LOG}" >&2
done
