#!/bin/bash
set -e

. setdevkitpath.sh
  
$NDK/build/tools/make-standalone-toolchain.sh \
	--arch=${TARGET_SHORT} \
	--platform=android-19 \
	--install-dir=$GITHUB_WORKSPACE/android-toolchain
cp devkit.info.${TARGET_SHORT} $GITHUB_WORKSPACE/android-toolchain/
