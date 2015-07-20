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
 * \file msrv_alloc.h
 * \date 2015
 */

#ifndef MINISERV_MSRV_ALLOC_H
#define MINISERV_MSRV_ALLOC_H

/* PKG includes
 */
#include <msrv/msrv_sym.h>

/* STDLIB includes
 */
#include <stdlib.h>
#include <string.h>

#if !defined(NDEBUG)

MSRV_API
/**
 *
 */
void* msrv_allocate_debug(size_t sz, const char* file, int line);

MSRV_API
/**
 *
 */
void msrv_deallocate_debug(void* mem);

MSRV_API
/**
 *
 */
void* msrv_callocate_debug(size_t sz, const char* file, int line);

/**
 *
 */
#  define msrv_alloc(x) msrv_allocate_debug((x), __FILE__, __LINE__)

/**
 *
 */
#  define msrv_calloc(x) msrv_callocate_debug((x), __FILE__, __LINE__)

/**
 *
 */
#  define msrv_free(x)  msrv_deallocate_debug((x))

#else/* Release */

MSRV_API
/**
 *
 */
void* msrv_allocate(size_t sz);

MSRV_API
/**
 *
 */
void msrv_deallocate(void* mem);

MSRV_API
/**
 *
 */
void* msrv_callocate(size_t sz);

/**
 *
 */
#  define msrv_alloc(x) msrv_allocate((x))

/**
 *
 */
#  define msrv_calloc(x) msrv_callocate((x))

/**
 *
 */
#  define msrv_free(x)  msrv_deallocate((x))

#endif/*!defined(NDEBUG)*/

#endif//MINISERV_MSRV_ALLOC_H

