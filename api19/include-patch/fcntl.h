__BEGIN_DECLS
  
int open64(const char* __path, int __flags, ...);

int fallocate(int __fd, int __mode, off_t __offset, off_t __length) __RENAME_IF_FILE_OFFSET64(fallocate64);
int fallocate64(int __fd, int __mode, off64_t __offset, off64_t __length);
int posix_fallocate(int __fd, off_t __offset, off_t __length) __RENAME_IF_FILE_OFFSET64(posix_fallocate64);
int posix_fallocate64(int __fd, off64_t __offset, off64_t __length);

__END_DECLS
