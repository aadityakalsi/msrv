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
 * \file msrv_log.c
 * \date 2015
 */

/* PKG includes
 */
#include <msrv/msrv_alloc.h>
#include <msrv/msrv_log.h>

/* STDLIB includes
 */
#include <stdarg.h>
#include <time.h>

struct msrv_logger_t
{
    FILE* file;
    int   level;
};

msrv_logger* msrv_create_logger_file(FILE* file, int loglevel)
{
    msrv_logger* log = (msrv_logger*)msrv_alloc(sizeof(*log));
    log->file = file;
    log->level = loglevel;
    return log;
}

msrv_logger* msrv_create_logger_filename(const char* file, int loglevel)
{
    FILE* f = fopen(file, "wb");
    if (!f) { return NULL; }
    return msrv_create_logger_file(f, loglevel);
}

void msrv_destroy_logger(msrv_logger* log)
{
    if (!log) { return; }
    {
        FILE* f = log->file;
        if (f && (f != stdout) && (f != stderr)) { fclose(f); }
    }
    msrv_free(log);
}

void msrv_log(msrv_logger* log, int level, const char* fmt, ...)
{
    if (log && (level > log->level)) { return; }
    if (!log->file) { return; }

    char timestamp[500];
    {/* timestamp */
        time_t ltime;
        ltime = time(NULL);
        strftime(timestamp, 500, "%x %X %p", localtime(&ltime));
    }

    const char* lvlstr = NULL;
    {/* extract level */
        switch (level) {
            case MSRV_LOG_INFO : lvlstr = "INFO "; break;
            case MSRV_LOG_WARN : lvlstr = "WARN "; break;
            case MSRV_LOG_ERR  : lvlstr = "ERR  "; break;
            case MSRV_LOG_FATAL: lvlstr = "FATAL"; break;
            default: lvlstr = "UNKWN"; break;
        }
    }

    fprintf(log->file, "[MSRV_LOG] | %s | %s | ", lvlstr, timestamp);
    va_list arglist;
    va_start(arglist, fmt);
    vfprintf(log->file, fmt, arglist);
    va_end(arglist);
    fputc('\n', log->file);
}

void msrv_log_set_level(msrv_logger* log, int level)
{
    log->level = level;
}

