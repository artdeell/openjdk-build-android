#!/bin/bash
set -e

if [ "$BUILD_IOS" != "1" ]; then

unset AR AS CC CXX LD OBJCOPY RANLIB STRIP CPPFLAGS LDFLAGS
git clone https://github.com/termux/termux-elf-cleaner
cd termux-elf-cleaner
make CFLAGS=__ANDROID_API__=24 termux-elf-cleaner
chmod +x termux-elf-cleaner
cd ..

findexec() { find $1 -type f -name "*" -not -name "*.o" -exec sh -c '
    case "$(head -n 1 "$1")" in
      ?ELF*) exit 0;;
      MZ*) exit 0;;
      #!*/ocamlrun*)exit0;;
    esac
exit 1
' sh {} \; -print
}

findexec jreout | xargs -- ./termux-elf-cleaner/termux-elf-cleaner
findexec jdkout | xargs -- ./termux-elf-cleaner/termux-elf-cleaner

fi

sudo cp -R jre_override/lib/* jreout/lib/
sudo cp -R jre_override/lib/* jdkout/jre/lib

cd jreout
#chmod 777 lib/aarch32/libapi19.so
#chmod 777 lib/aarch32/client/libjvm.so
sudo patchelf --add-needed libgnustl_shared.so lib/aarch32/libapi19.so
sudo patchelf --add-needed libapi19.so lib/aarch32/client/libjvm.so
sudo patchelf --set-rpath '$ORIGIN:$ORIGIN/..' lib/aarch32/client/libjvm.so
sudo patchelf --set-rpath '$ORIGIN' lib/aarch32/libapi19.so
sudo tar cJf ../jre8-${TARGET_SHORT}-`date +%Y%m%d`-${JDK_DEBUG_LEVEL}.tar.xz .

cd ../jdkout
sudo tar cJf ../jdk8-${TARGET_SHORT}-`date +%Y%m%d`-${JDK_DEBUG_LEVEL}.tar.xz .

