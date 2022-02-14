#!/bin/bash
set -e

. setdevkitpath.sh
  
$NDK/build/tools/make-standalone-toolchain.sh \
	--system=linux-x86_64 \
	--arch=${TARGET_SHORT} \
	--platform=android-$API \
	--install-dir=$NDK/generated-toolchains/android-${TARGET_SHORT}-toolchain
cp devkit.info.${TARGET_SHORT} $NDK/generated-toolchains/android-${TARGET_SHORT}-toolchain/

$ANDROID_NDK_HOME/build/tools/make-standalone-toolchain.sh \
	--arch=${TARGET_SHORT} \
	--platform=android-$API \
	--install-dir=$GITHUB_WORKSPACE/android-toolchain
