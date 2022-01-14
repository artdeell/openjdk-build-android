#!/bin/bash
set -e
. setdevkitpath.sh

API19="$(pwd)/api19"
JDKOUT=openjdk/build/${JVM_PLATFORM}-${TARGET_JDK}-normal-${JVM_VARIANTS}-${JDK_DEBUG_LEVEL}

if [ "$BUILD_IOS" != "1" ] && [ "$API" == "19" ]; then

cd $API19
$CC -v -c -I$API19/include *.c
$CXX -v -c -I$API19/include -std=c++11 *.cpp
find . | grep .o

cpo () { mkdir -p "$JDKOUT/objs/$2/" && cp "&1" "&_"; }
cpo *32*.o libtinyiconv

fi
