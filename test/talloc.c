/**
 * \file talloc.c
 * \date 2015
 */

#if defined(_WIN32)
#  define _CRT_SECURE_NO_WARNINGS
#  define GETCWD _getcwd
#  define CHDIR  _chdir
#include <direct.h>
#else
#  define _XOPEN_SOURCE 600
#  define GETCWD getcwd
#  define CHDIR  chdir
#include <unistd.h>
#endif/*defined(_WIN32)*/

#include "unittest.h"


/* STDLIB includes
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* TEST includes
 */
#include <msrv/msrv_alloc.h>

#if !defined(NDEBUG)

int exists(const char* n)
{
    FILE* f = fopen(n, "rb");
    if (f) { fclose(f); }
    return f != NULL;
}

static char FIND_EXE_BUFF[500];

void put_name(const char* pre, const char* name)
{
    strcpy((char*)FIND_EXE_BUFF, "");
    strcat((char*)FIND_EXE_BUFF, pre);
    strcat((char*)FIND_EXE_BUFF, name);
#if defined(_WIN32)
    strcat((char*)FIND_EXE_BUFF, ".exe");
#endif/*defined(_WIN32)*/
}

const char* find_exe(const char* str)
{
    put_name("./", str);
    if (exists(FIND_EXE_BUFF)) { return FIND_EXE_BUFF; }
    put_name("../", str);
    if (exists(FIND_EXE_BUFF)) { return FIND_EXE_BUFF; }
    put_name("../../", str);
    if (exists(FIND_EXE_BUFF)) { return FIND_EXE_BUFF; }
    return NULL;
}

void get_exe_dir(char* buf, size_t s)
{
    strcpy(buf, EXE_NAME);
#if defined(_WIN32)
    while (*buf) {
        *(buf++) = (*buf == '\\') ? '/' : *buf;
    }
#endif/*defined(_WIN32)*/
}

TEST_FUNC( hleak )
{
    char curdir[1024];
    char* lst = NULL;
    get_exe_dir(curdir, 1024);
    lst = strrchr(curdir,'/');
    TEST_TRUE( lst );
    *lst = '\0';
    chdir( curdir );
    const char* path = find_exe("hleak");
    TEST_TRUE( path );
    TEST_TRUE( system(path) != 0 );
}

#endif/*defined(NDEBUG)*/

TEST_FUNC( alloc_free )
{
    void* p = msrv_alloc(50);
    TEST_TRUE( p );
    msrv_free(p);
    TEST_FALSE( p );
}

void SetupTests(void)
{
    /* Correctness tests */
    REG_TEST( alloc_free );
#if !defined(NDEBUG)
    REG_TEST( hleak );
#endif/*defined(NDEBUG)*/
}
