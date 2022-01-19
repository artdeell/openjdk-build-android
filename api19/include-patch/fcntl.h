__BEGIN_DECLS
  
int creat64(const char* __path, mode_t __mode);
int openat64(int __dir_fd, const char* __path, int __flags, ...);
int open64(const char* __path, int __flags, ...);

__END_DECLS
