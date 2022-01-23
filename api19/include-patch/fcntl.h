__BEGIN_DECLS
  
int creat64(const char* __path, mode_t __mode);
int openat64(int __dir_fd, const char* __path, int __flags, ...);
int open64(const char* __path, int __flags, ...);

int posix_fallocate(int __fd, off_t __offset, off_t __length) __RENAME_IF_FILE_OFFSET64(posix_fallocate64);
int posix_fallocate64(int __fd, off64_t __offset, off64_t __length);

__END_DECLS
