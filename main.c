#define STDOUT 1
 
#define SYS_write 1
#define SYS_exit 60

typedef unsigned long long int uint64;

_Noreturn void exit(int code)
{
    /* Infinite for-loop since this function can't return */
    for (;;) {
        asm("mov %0, %%rax\n\t"
            "mov %1, %%rdi\n\t"
            "syscall\n\t"
            :
            : "r" ((uint64) SYS_exit),
              "r" ((uint64) code)
            : "%rax", "%rdi");
    }
}

int write(int fd, const char *buf, int length)
{
    int ret;

    __asm volatile (
        "syscall"
        : "=a"(ret)
        : "a"(SYS_write), "D"(fd), "S"(buf), "d"(length)
        : "rcx", "r11", "memory"
    );

    return ret;
}

int strlen(const char *str)
{
    const char *i = str;
    for (; *i; i++);
    return i - str;
}

int main(void)
{
    const char *msg = "Hello, World!\n";

    write(STDOUT, msg, strlen(msg));

    return 0;
}

__asm (
    ".global _start\n"
    "_start:\n"
    "   movl  (%rsp), %edi\n"
    "   lea   8(%rsp), %rsi\n"
    "   call  main\n"
    "   movl  %eax, %edi\n"
    "   movl  $60, %eax\n"
    "   syscall\n"
);