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
cmake ../test/
make -j8
for TEST in "gpio-util-test" "register-util-test"
do
    ./${TEST}
done
popd

yecho ""
yecho "Tests passed."
yecho ""
