#include_next <fcntl.h>

__strong_alias(creat64, creat);
__strong_alias(open64, open);
__strong_alias(openat64, openat);
