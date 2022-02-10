#!/bin/bash
set -e
. setdevkitpath.sh

export JDK_DEBUG_LEVEL=release

if [ "$BUILD_IOS" != "1" ]; then
  sudo apt update
  sudo apt -y install autoconf python unzip zip
  export NDK=$ANDROID_NDK_HOME
  ./maketoolchain.sh
else
  chmod +x ios-arm64-clang
  chmod +x ios-arm64-clang++
  chmod +x macos-host-cc
fi

# Some modifies to NDK to fix

./getlibs.sh
./buildlibs.sh
./clonejdk.sh
./buildjdk.sh
./removejdkdebuginfo.sh
./tarjdk.sh
