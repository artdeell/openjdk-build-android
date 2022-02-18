## api19

hi there, welcome to libapi19  
this is a collection of bionic sources that implement missing functions in kitkat (now gingerbread?) libc for openjdk building  

### use  
warning: I built libapi19 only with generated r21 toolchain, older ones may not work  
Copy `include-ndk/*` to `$GENERATED_TOOLCHAIN/sysroot/usr/include`,  
then simply build it as a shared library and link where `undefined referenece` happens.  
Also you may need to explicitly add C++ STL to "needed" libraries list in `libapi19.so`, for example `libgnustl_shared.so`.  
See `../setdevkitpath.sh`, `../buildjdk.sh`, `../tarjdk.sh`.  
  
### notes
`include-ndk/` contains ndk r21 unified headers, works as a drop-in replacement for old platform headers.  
Why? Well, cuz [platform headers](https://android.googlesource.com/platform/ndk/+/refs/tags/ndk-r21e/docs/UnifiedHeaders.md) are mess, for same reason `lib/libc.so` exists.  
`include-ndk/android/api-level.h` have some hardcoded defines cause of how openjdk c/cpp/cxx flags work (they don't).  
`syscalls/` and `include-ndk/asm/` are armv7 only

new flags  
**-DNOINLINE_SIGNAL** - disable legacy inline definition of `signal`, used for libjsig as it redefines that function  
**-DNEW_UCHAR** - use new uchar.h, used for libapi19
