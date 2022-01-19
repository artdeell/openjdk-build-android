#!/bin/bash
set -e
. setdevkitpath.sh

# patch toolchain, build libapi19, copy
if [ ! -e ./api19/libapi19.a ];
then
cd api19/include-patch
find . -name "*.h" -type f | sed 's#./##g' | xargs -I {} cat {} >> "$ANDROID_INCLUDE"/{}
cd ..
find . -name "*.cpp" -type f | xargs $CXX -c
$AR rc ./libapi19.a *.o
# well, maybe someday there won't be just one folder in setdevkitpath.sh
# also copy to toolchain (?)
LDFLAGS="$LDFLAGS $TOOLCHAIN/sysroot/usr/lib"
echo "$LDFLAGS" | sed 's#-L##g' | xargs -n 1 cp libapi19.a
cd ..
fi

# patch sources
if [ -d ./openjdk ];
then
cd ./openjdk
find . -name "*.gmk" -type f | xargs sed -i 's/-lc/-lc -lapi19/g'
cd ..
fi
