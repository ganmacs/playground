#!/bin/sh

set -eu

REPOSITORY_ROOT=$(cd "$(dirname $0)" && cd .. && pwd)

pushd "${REPOSITORY_ROOT}/bootstrap"
kubectl apply -f namespace.yaml
kubectl apply -k .
kubectl apply -f system-component.yaml
popd
