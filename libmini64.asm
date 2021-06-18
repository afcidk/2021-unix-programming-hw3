global sys_alarm:function
global sys_pause:function
global sys_exit:function
global sys_rt_sigpending:function
global sys_rt_sigaction:function
global sys_rt_sigprocmask:function
global sys_rt_sigreturn:function
global _setjmp_1:function
global _setjmp_2:function
global _longjmp:function

_setjmp_1:
    ; store registers
    mov     rcx, [rsp + 0x30]
    mov     qword[rdi], rcx 
    mov     qword[rdi+8], rsp
    mov     qword[rdi+16], rbp
    mov     qword[rdi+24], rbx
    mov     qword[rdi+32], r12
    mov     qword[rdi+40], r13
    mov     qword[rdi+48], r14
    mov     qword[rdi+56], r15
    ret

_setjmp_2:
    xor     rax, rax
    jmp     rcx

_longjmp:
    ; restore registers
    mov     rcx, qword[rdi]
    mov     rsp, qword[rdi+8]
    mov     rbp, qword[rdi+16]
    mov     rbx, qword[rdi+24]
    mov     r12, qword[rdi+32]
    mov     r13, qword[rdi+40]
    mov     r14, qword[rdi+48]
    mov     r15, qword[rdi+56]

    ; return value
    mov     rax, rsi
    test    rax, rax
    jnz     not_zero
    inc     rax     ; fake return if val = 0
not_zero:
    jmp     rcx

sys_alarm:
    mov     rax, 37     ; sys_alarm
    syscall
    ret

sys_rt_sigpending:
    mov     rax, 127    ; sys_rt_sigpending
    syscall
    ret

sys_rt_sigaction:
    mov     r10, rcx
    mov     rax, 13     ; sys_rt_sigaction
    syscall
    ret

sys_rt_sigprocmask:
    ; kernel-level calling convention: rdi, rsi, rdx, r10, r8, r9
    ; user-level calling convention:   rdi, rsi, rdx, rcx, r8, r9
    mov     r10, rcx
    mov     rax, 14     ; sys_rt_sigprocmask
    syscall
    ret

sys_rt_sigreturn:
    mov     rax, 15
    syscall
    ret
