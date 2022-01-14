#!/bin/bash
set -e
. setdevkitpath.sh
API19="$(pwd)/api19"
if [ "$BUILD_IOS" != "1" ] && [ "$API" == "19" ]; then
cd $API19
$CC -v -c -I$API19/include *.c
$CXX -v -c -I$API19/include -std=c++11 *.cpp
find .
fi
exit 1
