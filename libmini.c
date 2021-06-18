#include "libmini.h"

extern long sys_alarm(unsigned int seconds);
extern long sys_rt_sigpending(sigset_t *set, size_t sigsetsize);
extern long sys_rt_sigaction(int signum, const sigaction_t *act, sigaction_t *oldact, size_t sigsetsize);
extern long sys_rt_sigprocmask(int how, sigset_t *nset, sigset_t *oldset, size_t sigsetsize);
extern void sys_rt_sigreturn(void);
extern int  _setjmp_1(jmp_buf env);
extern int  _setjmp_2();
extern void _longjmp(jmp_buf env, int val);

long alarm(unsigned int seconds) {
    return sys_alarm(seconds);
}

long sigpending(sigset_t *set) {
    return sys_rt_sigpending(set, sizeof(sigset_t));
}

sighandler_t signal(int signum, sighandler_t handler) {
    sigaction_t act, oldact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, signum);
    sigaction(signum, &act, &oldact);
    return oldact.sa_handler;
}

int sigaction(int signum, const sigaction_t *act, sigaction_t *oldact) {
    sigaction_t newact = *act;
    newact.sa_flags |= SA_RESTORER | SA_RESTART;
    newact.sa_restorer = sys_rt_sigreturn;
    return sys_rt_sigaction(signum, &newact, oldact, sizeof(sigset_t));
}

int setjmp(jmp_buf env) {
    /* Store sigset */
    _setjmp_1(env); // Store registers first
    sigset_t oldset;
    sigprocmask(0, NULL, &oldset);
    env->mask = oldset;
    return _setjmp_2();
}

void longjmp(jmp_buf env, int val) {
    sigprocmask(SIG_SETMASK, &env->mask, NULL);
    _longjmp(env, val);
}

long sigprocmask(int how, sigset_t *nset, sigset_t *oldset) {
    return sys_rt_sigprocmask(how, nset, oldset, sizeof(sigset_t));
}

void *memset(void *s, int c, size_t n) {
    int *p = (int*)s;
    int x = c & 0xff;
    x |= x << 8;
    x |= x << 16;
    n >>= 2;
    while (n--) *p++ = x;
    return p;
}

void sigemptyset(sigset_t *set) {
    memset(set, 0, sizeof(sigset_t));
}

void sigfillset(sigset_t *set) {
    memset(set, -1, sizeof(sigset_t));
}

void sigaddset(sigset_t *set, int signum) {
    int sig = signum-1;
    set->sig[sig/_NSIG_BPW] |= 1UL << (sig % _NSIG_BPW);
}
void sigdelset(sigset_t *set, int signum) {
    int sig = signum-1;
    set->sig[sig/_NSIG_BPW] &= ~(1UL << (sig % _NSIG_BPW));
}
int sigismember(const sigset_t *set, int signum) {
    int sig = signum-1;
    return 1 & (set->sig[sig/_NSIG_BPW] >> (sig % _NSIG_BPW));
}
