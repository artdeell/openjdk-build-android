#include <signal.h>
#include <ErrnoRestorer.h>

int pthread_sigmask(int how, const sigset_t* new_set, sigset_t* old_set) {
  ErrnoRestorer errno_restorer;
  return (sigprocmask(how, new_set, old_set) == -1) ? errno : 0;
}
