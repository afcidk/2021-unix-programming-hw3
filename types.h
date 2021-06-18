#ifndef TYPES_H
#define TYPES_H


typedef struct {
    unsigned long sig[1];
} sigset_t;

typedef union sigval {
    int sival_int;
    void *sival_ptr;
} sigval_t;

typedef struct {
    int si_signo;
    int si_code;
    sigval_t si_value;
    int si_errno;
    pid_t si_pid;
    uid_t si_uid;
    void *si_addr;
    int si_status;
    int si_band;
} siginfo_t;

typedef struct {
    void (*sa_handler)(int);
    unsigned long sa_flags;
    void (*sa_restorer)(void);
    sigset_t sa_mask;
} sigaction_t;

typedef struct jump_buf_s {
    long long reg[8];
    sigset_t mask;
} jmp_buf[1];

#endif
