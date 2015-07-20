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
 * \file msrv_sym.h
 * \date 2015
 */

#ifndef MINISERV_MSRV_SYM_H
#define MINISERV_MSRV_SYM_H

#if defined(_WIN32)
#  define _CRT_SECURE_NO_WARNINGS
#endif/*defined(_WIN32)*/

#if defined(MSRV_BUILD)
#  ifdef _MSC_VER
#    define MSRV_API __declspec(dllexport)
#  else
#    define MSRV_API __attribute__((__visibility__("default")))
#  endif
#else
#  ifdef _MSC_VER
#    define MSRV_API __declspec(dllimport)
#  else
#    define MSRV_API
#  endif
#endif

#if !defined(MSRV_INL)
#  if defined(_MSC_VER)
#    define MSRV_INL __forceinline
#  else/*GCC like compiler*/
#    define MSRV_INL __inline__ __attribute__((always_inline))
#  endif/*defined(_MSC_VER)*/
#endif/*defined(MSRV_INL)*/

#if !defined(MSRV_PRV)
#  define MSRV_PRV static
#endif/*defined(MSRV_PRV)*/

#if !defined(MSRV_DEBUG) && !defined(NDEBUG)
#  define MSRV_DEBUG 1
#else
#  define MSRV_DEBUG 0
#endif/*defined(MSRV_DEBUG)*/

#endif//MINISERV_MSRV_SYM_H

