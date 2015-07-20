/**
* \file tlog.c
* \date 2015
*/

/* TEST includes
 */
#include <msrv/msrv_log.h>

#include "unittest.h"

#include <string.h>

const char* exedir()
{
    static char EXEDIR[1024];
    static int IS_DONE = 0;
    if (IS_DONE) { return EXEDIR; }
    strcpy(EXEDIR, "");
    strcat(EXEDIR, EXE_NAME);
#if defined(_MSC_VER)
    {
        char* buf = EXEDIR;
        while (*buf) { *(buf++) = (*buf == '\\') ? '/' : *buf; }
    }
#endif/*defined(_MSC_VER)*/
    char* lst = strrchr(EXEDIR, '/');
    *lst = '\0';
    IS_DONE = 1;
    return EXEDIR;
}

TEST_FUNC( log_create_info )
{
    char tmname[1024];
    strcpy(tmname, exedir());
    strcat(tmname, "/log1.txt");
    msrv_logger* log = msrv_create_logger_filename(tmname, MSRV_LOG_INFO);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
    /* count lines */
    {
        FILE* f = fopen(tmname, "rb");
        char ch = '\0';
        int nlines = 0;
        while ((ch = fgetc(f)) != EOF) { nlines += (ch == '\n'); }
        TEST_TRUE( nlines == 4 );
    }
    remove(tmname);
}

TEST_FUNC( log_create_warn )
{
    char tmname[1024];
    strcpy(tmname, exedir());
    strcat(tmname, "/log2.txt");
    msrv_logger* log = msrv_create_logger_filename(tmname, MSRV_LOG_WARN);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
    /* count lines */
    {
        FILE* f = fopen(tmname, "rb");
        char ch = '\0';
        int nlines = 0;
        while ((ch = fgetc(f)) != EOF) { nlines += (ch == '\n'); }
        TEST_TRUE( nlines == 3 );
    }
    remove(tmname);
}

TEST_FUNC( log_create_err )
{
    char tmname[1024];
    strcpy(tmname, exedir());
    strcat(tmname, "/log3.txt");
    msrv_logger* log = msrv_create_logger_filename(tmname, MSRV_LOG_ERR);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
    /* count lines */
    {
        FILE* f = fopen(tmname, "rb");
        char ch = '\0';
        int nlines = 0;
        while ((ch = fgetc(f)) != EOF) { nlines += (ch == '\n'); }
        TEST_TRUE( nlines == 2 );
    }
    remove(tmname);
}

TEST_FUNC( log_create_fatal )
{
    char tmname[1024];
    strcpy(tmname, exedir());
    strcat(tmname, "/log4.txt");
    msrv_logger* log = msrv_create_logger_filename(tmname, MSRV_LOG_FATAL);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
    /* count lines */
    {
        FILE* f = fopen(tmname, "rb");
        char ch = '\0';
        int nlines = 0;
        while ((ch = fgetc(f)) != EOF) { nlines += (ch == '\n'); }
        TEST_TRUE( nlines == 1 );
    }
    remove(tmname);
}

TEST_FUNC( log_create_stdout_info )
{
    msrv_logger* log = msrv_create_logger_file(stdout, MSRV_LOG_INFO);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
}

TEST_FUNC( log_create_stdout_warn )
{
    msrv_logger* log = msrv_create_logger_file(stdout, MSRV_LOG_WARN);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
}

TEST_FUNC( log_create_stdout_err )
{
    msrv_logger* log = msrv_create_logger_file(stdout, MSRV_LOG_ERR);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
}

TEST_FUNC( log_create_stdout_fatal )
{
    msrv_logger* log = msrv_create_logger_file(stdout, MSRV_LOG_FATAL);
    {
        msrv_log(log, MSRV_LOG_INFO , "foo");
        msrv_log(log, MSRV_LOG_WARN , "foo");
        msrv_log(log, MSRV_LOG_ERR  , "foo");
        msrv_log(log, MSRV_LOG_FATAL, "foo");
    }
    msrv_destroy_logger(log);
}

void SetupTests(void)
{
    /* Correctness tests */
    REG_TEST( log_create_info );
    REG_TEST( log_create_warn );
    REG_TEST( log_create_err );
    REG_TEST( log_create_fatal );
    REG_TEST( log_create_stdout_info );
    REG_TEST( log_create_stdout_warn );
    REG_TEST( log_create_stdout_err );
    REG_TEST( log_create_stdout_fatal );
}
