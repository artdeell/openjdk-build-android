/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <ctype.h>
#include <errno.h>
#include <grp.h>
#include <mntent.h>
#include <pthread.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#include <android_filesystem_config.h>
#include <bionic_macros.h>
#include <grp_pwd.h>
#include <ErrnoRestorer.h>

// Generated android_ids array
//#include "generated_android_ids.h"
//#include "grp_pwd_file.h"

//static PasswdFile vendor_passwd("/vendor/etc/passwd", "vendor_");
//static GroupFile vendor_group("/vendor/etc/group", "vendor_");

// POSIX seems to envisage an implementation where the <pwd.h> functions are
// implemented by brute-force searching with getpwent(3), and the <grp.h>
// functions are implemented similarly with getgrent(3). This means that it's
// okay for all the <grp.h> functions to share state, and all the <passwd.h>
// functions to share state, but <grp.h> functions can't clobber <passwd.h>
// functions' state and vice versa.
#include <pthread_internal.h>
static group_state_t* get_group_tls_buffer() {
  return &__get_bionic_tls().group;
}

static passwd_state_t* get_passwd_tls_buffer() {
  return &__get_bionic_tls().passwd;
}

static void init_group_state(group_state_t* state) {
  memset(state, 0, sizeof(group_state_t) - sizeof(state->getgrent_idx));
  state->group_.gr_mem = state->group_members_;
}

static group_state_t* __group_state() {
  group_state_t* result = get_group_tls_buffer();
  if (result != nullptr) {
    init_group_state(result);
  }
  return result;
}

static int do_getpw_r(int by_name, const char* name, uid_t uid,
                      passwd* dst, char* buf, size_t byte_count,
                      passwd** result) {
  // getpwnam_r and getpwuid_r don't modify errno, but library calls we
  // make might.
  ErrnoRestorer errno_restorer;
  *result = nullptr;

  // Our implementation of getpwnam(3) and getpwuid(3) use thread-local
  // storage, so we can call them as long as we copy everything out
  // before returning.
  const passwd* src = by_name ? getpwnam(name) : getpwuid(uid); // NOLINT: see above.

  // POSIX allows failure to find a match to be considered a non-error.
  // Reporting success (0) but with *result NULL is glibc's behavior.
  if (src == nullptr) {
    return (errno == ENOENT) ? 0 : errno;
  }

  // Work out where our strings will go in 'buf', and whether we've got
  // enough space.
  size_t required_byte_count = 0;
  dst->pw_name = buf;
  required_byte_count += strlen(src->pw_name) + 1;
  dst->pw_dir = buf + required_byte_count;
  required_byte_count += strlen(src->pw_dir) + 1;
  dst->pw_shell = buf + required_byte_count;
  required_byte_count += strlen(src->pw_shell) + 1;
  if (byte_count < required_byte_count) {
    return ERANGE;
  }

  // Copy the strings.
  snprintf(buf, byte_count, "%s%c%s%c%s", src->pw_name, 0, src->pw_dir, 0, src->pw_shell);

  // pw_passwd and pw_gecos are non-POSIX and unused (always NULL) in bionic.
  // Note: On LP32, we define pw_gecos to pw_passwd since they're both NULL.
  dst->pw_passwd = nullptr;
#if defined(__LP64__)
  dst->pw_gecos = nullptr;
#endif

  // Copy the integral fields.
  dst->pw_gid = src->pw_gid;
  dst->pw_uid = src->pw_uid;

  *result = dst;
  return 0;
}

int getpwnam_r(const char* name, passwd* pwd,
               char* buf, size_t byte_count, passwd** result) {
  return do_getpw_r(1, name, -1, pwd, buf, byte_count, result);
}

int getpwuid_r(uid_t uid, passwd* pwd,
               char* buf, size_t byte_count, passwd** result) {
  return do_getpw_r(0, nullptr, uid, pwd, buf, byte_count, result);
}
