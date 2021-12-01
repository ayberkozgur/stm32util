#!/bin/bash

set -e

function yecho(){
    echo -e "\033[1;33m$1\033[0m"
}

yecho ""
yecho "Testing stm32util..."
yecho ""

mkdir -p build-test
pushd build-test
if [[ $(uname -s) == MINGW* ]]; then
    cmake -G"MinGW Makefiles" ../test/
else
    cmake ../test/
fi
cmake --build .
for TEST in "gpio-util-test" "register-util-test"
do
    ./${TEST}
done
popd

yecho ""
yecho "Tests passed."
yecho ""
