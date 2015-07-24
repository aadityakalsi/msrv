/**
 * \file talloc.c
 * \date 2015
 */

#include "unittest.h"

/* TEST includes
 */
#include <msrv/msrv_stdint.h>
#include <msrv/msrv_inttypes.h>

TEST_FUNC( int_defs )
{
    uint8_t  u8  = 0;
    int8_t   i8  = 0;
    uint16_t u16 = 0;
    int16_t  i16 = 0;
    uint32_t u32 = 0;
    int32_t  i32 = 0;
    uint64_t u64 = 0;
    int64_t  i64 = 0;

    TEST_FALSE( u8  );
    TEST_FALSE( i8  );
    TEST_FALSE( u16 );
    TEST_FALSE( i16 );
    TEST_FALSE( u32 );
    TEST_FALSE( i32 );
    TEST_FALSE( u64 );
    TEST_FALSE( i64 );
}

void SetupTests(void)
{
    REG_TEST( int_defs );
}
