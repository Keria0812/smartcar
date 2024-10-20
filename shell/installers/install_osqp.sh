#!/usr/bin/env bash

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
git clone https://gitee.com/xiacanming/osqp-0.62.git

pushd osqp-0.62/osqp
mkdir build && cd build
cmake ../
make
make install
popd

git clone https://gitee.com/xiacanming/osqp-eigen-0.62.git
pushd osqp-eigen-0.62/osqp-eigen
mkdir build && cd build
cmake ../
make
make install
popd

#Clean
apt-get clean && rm -rf /var/lib/apt/lists/*
rm -fr osqp-0.62
rm -fr osqp-eigen-0.62
