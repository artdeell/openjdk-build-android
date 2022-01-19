#!/bin/bash
set -e
. setdevkitpath.sh

# build libapi19.a
if [ ! -e ./api19/libapi19.a ]
cd api19
find . -name "*.cpp" -type f | xargs $CXX -c -I./include
$AR rc ./libapi19.a *.o
cd ..
fi

# patch sources
if [ -d ./openjdk ]
cd ./openjdk
find . -name "*.gmk" -type f | xargs sed -i 's/-lc/-lc -lapi19/g'
cd ..
fi
