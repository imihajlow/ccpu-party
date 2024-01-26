#!/bin/bash

set -e

if ! which cargo
then
    echo Install rust!
    exit 1
fi

if ! which pip3
then
    echo Install python3!
    exit 1
fi

cd $(dirname $0)/..

if [[ -d ccpu ]]
then
    cd ccpu
    git pull
    cd ..
else
    git clone https://github.com/imihajlow/ccpu.git
fi

if [[ -d ccpu-cc ]]
then
    cd ccpu-cc
    git pull
    cd ..
else
    git clone https://github.com/imihajlow/ccpu-cc.git
fi

if [[ -d ccpu-libc ]]
then
    cd ccpu-libc
    git pull
    cd ..
else
    git clone https://github.com/imihajlow/ccpu-libc.git
fi

if [[ -d ccpu-libsys ]]
then
    cd ccpu-libsys
    git pull
    cd ..
else
    git clone https://github.com/imihajlow/ccpu-libsys.git
fi

cargo install --path ccpu-cc
cargo install --path ccpu/tools/rsim

pip3 install -r ccpu/tools/requirements.txt

cd ccpu-libc && make -j 12 && cd ..

cd ccpu-libsys && make -j 12 && cd ..

