#include <signal.h>
#include <ErrnoRestorer.h>

int pthread_sigmask(int how, const sigset_t* new_set, sigset_t* old_set) {
  ErrnoRestorer errno_restorer;
  return (sigprocmask(how, new_set, old_set) == -1) ? errno : 0;
}
template <typename SigSetT>
int SigAddSet(SigSetT* set, int sig) {
  int bit = sig - 1; // Signal numbers start at 1, but bit positions start at 0.
  unsigned long* local_set = reinterpret_cast<unsigned long*>(set);
  if (set == nullptr || bit < 0 || bit >= static_cast<int>(8*sizeof(*set))) {
    errno = EINVAL;
    return -1;
  }
  local_set[bit / LONG_BIT] |= 1UL << (bit % LONG_BIT);
  return 0;
}
int sigaddset64(sigset64_t* set, int sig) {
  return SigAddSet(set, sig);
}
template <typename SigSetT>
int SigDelSet(SigSetT* set, int sig) {
  int bit = sig - 1; // Signal numbers start at 1, but bit positions start at 0.
  unsigned long* local_set = reinterpret_cast<unsigned long*>(set);
  if (set == nullptr || bit < 0 || bit >= static_cast<int>(8*sizeof(*set))) {
    errno = EINVAL;
    return -1;
  }
  local_set[bit / LONG_BIT] &= ~(1UL << (bit % LONG_BIT));
  return 0;
}
int sigdelset64(sigset64_t* set, int sig) {
  return SigDelSet(set, sig);
}
template <typename SigSetT>
int SigEmptySet(SigSetT* set) {
  if (set == nullptr) {
    errno = EINVAL;
    return -1;
  }
  memset(set, 0, sizeof(*set));
  return 0;
}
int sigemptyset64(sigset64_t* set) {
  return SigEmptySet(set);
}
