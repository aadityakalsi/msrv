/**
 * \file talloc.c
 * \date 2015
 */

#include "unittest.h"

/* STDLIB includes
 */
#include <string.h>

/* TEST includes
 */
#include <msrv/msrv.h>

TEST_FUNC( version )
{
    TEST_TRUE( strcmp(msrv_version(), "0.1.1") == 0 );
}

void SetupTests(void)
{
    /* Correctness tests */
    REG_TEST( version );
}