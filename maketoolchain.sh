#!/bin/bash
set -e

. setdevkitpath.sh
  
$NDK/build/tools/make-standalone-toolchain.sh \
	--stl=$STL \
	--arch=${TARGET_SHORT} \
	--platform=android-$API \
	--install-dir=$NDK/generated-toolchains/android-${TARGET_SHORT}-toolchain
cp devkit.info.${TARGET_SHORT} $NDK/generated-toolchains/android-${TARGET_SHORT}-toolchain/
