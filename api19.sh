#!/bin/bash
set -e
. setdevkitpath.sh
API19="$(pwd)/api19"
if [ "$BUILD_IOS" != "1" ] && [ "$API" == "19" ]; then
cd $API19
$CC -c -I$API19/include *.c
$CXX -c -I$API19/include *.cpp
find . | grep *.o
fi
