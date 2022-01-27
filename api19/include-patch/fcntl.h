#include <stdarg.h>
#pragma once

__BEGIN_DECLS
  
int open64(const char* __path, int __flags, ...) {
  va_list args;
  va_start(args, __flags);
  int x = open(__path, __flags, args);
  va_end(args);
  return x;
}
int fallocate(int __fd, int __mode, off_t __offset, off_t __length) __RENAME_IF_FILE_OFFSET64(fallocate64);
int fallocate64(int __fd, int __mode, off64_t __offset, off64_t __length);
int posix_fallocate(int __fd, off_t __offset, off_t __length) __RENAME_IF_FILE_OFFSET64(posix_fallocate64);
int posix_fallocate64(int __fd, off64_t __offset, off64_t __length);

__END_DECLS
