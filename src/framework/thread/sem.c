//
//  sem.c
//  GHTTPd
//
//  Created by wangxingzhuo on 09/02/2018.
//  Copyright © 2018 watsserve. All rights reserved.
//

#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#include "sem.h"

int init_sem(sem_t *sem, int pshared, int value)
{
    if (pshared)
    {
        errno = ENOSYS;
        return -1;
    }
    *sem = dispatch_semaphore_create(value);
    if (NULL == *sem)
    {
        errno = EINVAL;
        return -1;
    }
    return 0;
}

int wait_sem(sem_t *sem)
{
    return (int)dispatch_semaphore_wait(*sem, DISPATCH_TIME_FOREVER);
}

int post_sem(sem_t *sem)
{
    dispatch_semaphore_signal(*sem);
    return 0;
}

int destroy_sem(sem_t *sem)
{
    dispatch_release(*sem);
    return 0;
}

#endif
