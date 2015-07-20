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
 * \file msrv_internal.h
 * \date 2015
 */

#ifndef MSRV_MSRV_INTERNAL_H
#define MSRV_MSRV_INTERNAL_H

#if defined(_WIN32)
#  define _CRT_SECURE_NO_WARNINGS
#endif/*defined(_WIN32)*/

/* STDLIB includes
 */
#include <stdio.h>      /* for fprintf(), stderr */
#include <stdlib.h>     /* for abort() */

/* PKG includes
 */
#include <msrv/msrv_sym.h>  /* for MSRV_DEBUG */

#define MSRV_ASSERT_ALWAYS_MSG(x, ...) \
  do { \
      if (!(x)) { \
          fprintf(stderr, "[MSRV ASSERT] file: %s  line: %d message: ", __FILE__, __LINE__); \
          fprintf(stderr, __VA_ARGS__); \
          abort(); \
      } \
  } while(0)

#if MSRV_DEBUG
#  define MSRV_ASSERT_MSG(x, ...) MSRV_ASSERT_ALWAYS_MSG(x, __VA_ARGS__)
#else/*no debugging*/
#  define MSRV_ASSERT_MSG(x, ...)
#endif/*MSRV_DEBUG*/

#if MSRV_DEBUG
#  define MSRV_ASSERT(x) MSRV_ASSERT_ALWAYS_MSG(x, "expression: %s\n", #x)
#else/*no debugging*/
#  define MSRV_ASSERT(x)
#endif/*MSRV_DEBUG*/

#endif//MSRV_MSRV_INTERNAL_H

