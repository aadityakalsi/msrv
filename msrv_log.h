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
 * \file msrv_log.h
 * \date 2015
 */

#ifndef MSRV_MSRV_LOG_H
#define MSRV_MSRV_LOG_H

/* PKG includes
 */
#include <msrv/msrv_sym.h>
#include <msrv/msrv_io.h>

struct msrv_logger_t;

/**
 *
 */
typedef struct msrv_logger_t msrv_logger;

#define MSRV_LOG_INFO  3
#define MSRV_LOG_WARN  2
#define MSRV_LOG_ERR   1
#define MSRV_LOG_FATAL 0

MSRV_API
/**
 *
 */
msrv_logger* msrv_create_logger_filename(const char* file, int loglevel);

MSRV_API
/**
 *
 */
msrv_logger* msrv_create_logger_file(FILE* file, int loglevel);

MSRV_API
/**
 *
 */
void msrv_destroy_logger(msrv_logger* log);

MSRV_API
/**
 *
 */
void msrv_log(msrv_logger* log, int level, const char* fmt, ...);

MSRV_API
/**
 *
 */
void msrv_log_set_level(msrv_logger* log, int level);

#endif//MSRV_MSRV_LOG_H
