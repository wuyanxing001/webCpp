//
//  Aio.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef Aio_h
#define Aio_h

extern "C" {
    #include <aio.h>
}
#include "G/Object.hpp"

#if defined(__linux__) || defined(__linux)
#define __LINUX__
#endif

#if defined(__APPLE__) || defined(__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#define __BSD__
#endif

/**
 *  UNIX or BSD
 */
#ifndef __LINUX__

#include "G/ThreadPool.hpp"

struct aioinit
{
    int aio_threads;   // Maximum number of threads
    int aio_num;       // Number of expected simultaneous requests
    int aio_idle_time;
};

#endif


/**
 *  MAC or BSD
 */
#ifdef __BSD__

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

typedef struct aio_back
{
    ssize_t dataLen;
    ssize_t doneLen;
    ssize_t sumSize;
    int error;
} AioBack;

#endif


/**
 *  all system not windows
 */

namespace G {
    class Aio : public Object {
        
    public:

    	// MAC or BSD
#ifdef __BSD__
        static int kq;
        static AioBack *rdList;
        static AioBack *wrList;
        static aioinit conf;
        static void* listenEvnt(void *);
        static void* readCallback(void *);
        static void* writeCallback(void *);
        static ThreadPool threadPool;

        // UNIX
#elif !defined(__LINUX__)
        static int pfd;

        // linux
#else
        static int epfd;
#endif
        static int aioInit(struct aioinit *);
        static int aioRead(struct aiocb *);
        static int aioWrite(struct aiocb *);
        static ssize_t aioReturn(struct aiocb *);
        static int aioError(const struct aiocb *);
        static int aioCancel(int, struct aiocb *);
    };
}

#endif /* Aio_h */
