/*
Copyright (c) 2015, Aaditya Kalsi
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list 
of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this 
list of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may 
be used to endorse or promote products derived from this software without specific 
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * \file msrv_alloc.c
 * \date 2015
 */

#if !defined(_MSC_VER)
#define _XOPEN_SOURCE 600
#endif/*!defined(_MSC_VER)*/

/* PKG includes
 */
#include <msrv/msrv_alloc.h>

/* PKG internal includes
 */
#include "msrv_internal.h"  /* MSRV_ASSERT() */

#if defined(_MSC_VER)
/*
 * On Windows, aligned APIs need malloc.h
 */
#include <malloc.h>
#include <Windows.h>
#endif/*defined(_MSC_VER)*/

#define ALIGN 64

void* msrv_allocate(size_t sz)
{
#if defined(_MSC_VER)
    return _aligned_malloc(sz, ALIGN);
#else
    void* mem = NULL;
    int ret = posix_memalign(&mem, ALIGN, sz);
    (void)ret;
    return mem;
#endif
}

void msrv_deallocate(void* mem)
{
#if defined(_MSC_VER)
    _aligned_free(mem);
#else
    free(mem);
#endif
}

void* msrv_callocate(size_t sz)
{
    void* p = msrv_allocate(sz);
    memset(p, 0, sz);
    return p;
}

#if MSRV_DEBUG

typedef struct malloc_info_t malloc_info;

struct malloc_info_t
{
   const char*  file;
   int          line;
   size_t       size;
   malloc_info* next;
   malloc_info* prev;
};

static malloc_info* S_HEAD;
static int          S_REG_EXIT = 0;

MSRV_PRV
int msrv_dumpmem(void)
{
    malloc_info *mi = S_HEAD;
    int ret = 0;
    while (mi) {
        if ((int)(mi->size) >= 0) {
            ret = 1;
            printf("MSRV_LEAKED: %s (%4d): %8llu bytes at %p\n", mi->file, mi->line, (unsigned long long)mi->size, mi+1);
            fflush(stdout);
        }
        mi = mi->next;
    }
#if defined(MSRV_DEBUG_MEM_SHOW_ALL)
    mi = S_HEAD;
    while (mi) {
        if ((ptrdiff_t) mi->size < 0) {
            printf("MSRV_FREED : %s (%4d): %8llu bytes at %p\n", mi->file, mi->line, (unsigned long long)~mi->size, mi+1);
        }
        mi = mi->next;
    }
#endif/*defined(MSRV_DEBUG_MEM_SHOW_ALL)*/
    return ret;
}

void msrv_dumpmem_s(void)
{
    if (msrv_dumpmem()) { exit(1); }
}

void* msrv_allocate_debug(size_t sz, const char* file, int line)
{
    malloc_info *mi = (malloc_info*)msrv_allocate(sz + sizeof(*mi));
    if (mi == NULL) return mi;
    mi->file = file;
    mi->line = line;
    mi->next = S_HEAD;
    if (S_HEAD) {
        mi->next->prev = mi;
    } else if (!S_REG_EXIT) {
        atexit(msrv_dumpmem_s);
    }
    mi->prev = NULL;
    mi->size = (int)sz;
    S_HEAD = mi;
    return mi + 1;
}

void msrv_deallocate_debug(void *ptr)
{
    if (ptr != NULL) {
        malloc_info *mi = (malloc_info*)ptr - 1;
        mi->size = ~mi->size;
#if !defined(MSRV_DEBUG_MEM_SHOW_ALL)
        if (mi->prev == NULL) {
            MSRV_ASSERT(S_HEAD == mi);
            S_HEAD = mi->next;
        } else {
            mi->prev->next = mi->next;
        }
        if (mi->next) {
            mi->next->prev = mi->prev;
        }
#endif/*!defined(MSRV_DEBUG_MEM_SHOW_ALL)*/
   }
}

void* msrv_callocate_debug(size_t sz, const char* file, int line)
{
    void* p = msrv_allocate_debug(sz, file, line);
    memset(p, 0, sz);
    return p;
}

#endif/*MSRV_DEBUG*/
