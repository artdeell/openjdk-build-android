#!/bin/bash
set -e
. setdevkitpath.sh

# patch toolchain, build libapi19, copy
#if [ ! -e ./api19/libapi19.a ];
#then
cd api19/include-patch
echo "$0: Patching includes"
find . -name "*.h" -type f | sed 's#./##g' | xargs -i  sh -c 'cat {} >> "$ANDROID_INCLUDE"/{}'
cd ../include
cp -rf * "$ANDROID_INCLUDE"/
cd ..
#echo "$0: Compiling sources"
#$CXX -shared -I. -o libapi19.so *.cpp arch-$TARGET_JDK/syscalls/*.S
#echo "$0: Building library"
#$AR rcv ./libapi19.a *.o
cd ..
#fi

# patch sources
#if [ -d ./openjdk ];
#then
#cd ./openjdk
#echo "$0: Patching OpenJDK makefiles"
#find . -name "*.gmk" -type f | xargs sed -i 's/(LIBDL)/(LIBDL) -lapi19/g'
#cd ..
#fi
