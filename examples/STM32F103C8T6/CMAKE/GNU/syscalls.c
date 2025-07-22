/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/* Variables */
//#undef errno
extern int errno;
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

// register unsigned char *__stack_ptr (__ASM("sp"));

// register unsigned char *__stack_ptr asm("sp");

char  *__env[1] = {0};
char **environ  = __env;

/* Functions */
void initialise_monitor_handles( )
{
}

int _getpid(void)
{
    return 1;
}

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

void _exit(int status)
{
    _kill(status, -1);
    while(1)
    {
    } /* Make sure we hang here */
}

/**
 * @brief scanf 的 call 支持 懒得写 没人用
 * @param file 
 * @param ptr 
 * @param len 
 * @return 
 */
__attribute__((weak)) int _read(int file, char *ptr, int len)
{
    int DataIdx;

    for(DataIdx = 0; DataIdx < len; DataIdx++)
    {
        *ptr++ = __io_getchar( );
    }

    return len;
}

/* 支持printf */
#include <HAL_Usart.h>
extern void Usart_SendArray(USART_TypeDef *pUSARTx, uint8_t *array, uint16_t num);
/**
 * @brief printf 的 call 支持
 * @param file 
 * @param ptr 
 * @param len 
 * @return 
 */
__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    int DataIdx;

    Usart_SendArray(DEBUG_USARTx, (uint8_t *)ptr, len);
    return len;
}

int _close(int file)
{
    return -1;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(char *path, int flags, ...)
{
    /* Pretend like we always fail */
    return -1;
}

int _wait(int *status)
{
    errno = ECHILD;
    return -1;
}

int _unlink(char *name)
{
    errno = ENOENT;
    return -1;
}

int _times(struct tms *buf)
{
    return -1;
}

int _stat(char *file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _link(char *old, char *new)
{
    errno = EMLINK;
    return -1;
}

int _fork(void)
{
    errno = EAGAIN;
    return -1;
}

int _execve(char *name, char **argv, char **env)
{
    errno = ENOMEM;
    return -1;
}
