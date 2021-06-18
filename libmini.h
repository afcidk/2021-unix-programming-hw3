#ifndef LIBMINI_H
#define LIBMINI_H
#include "libmini-inclass.h"
#include "types.h"

/* Function prototypes */
long alarm(unsigned int seconds);
long sigpending(sigset_t *set);
int sigaction(int signum, const sigaction_t *act, sigaction_t *oldact);
sighandler_t signal(int signum, sighandler_t handler);
long sigprocmask(int how, sigset_t *nset, sigset_t *oldset);
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
void sigemptyset(sigset_t *set);
void sigfillset(sigset_t *set);
void sigaddset(sigset_t *set, int signum);
void sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);

#endif
