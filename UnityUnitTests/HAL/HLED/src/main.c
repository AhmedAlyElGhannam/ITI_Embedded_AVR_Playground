#include "test.h"


int main(void)
{
    UNITY_BEGIN(); // unit test beginning

    /* HLED_voidInit test
    RUN_TEST(UTEST_HLED_voidInit_ValidEntriesInArr);*/

    // HLED_uint8SetLEDValue tests
    RUN_TEST(UTEST_HLED_uint8SetLEDValue_InvalidLEDName);
    RUN_TEST(UTEST_HLED_uint8SetLEDValue_InvalidLEDValue);
    RUN_TEST(UTEST_HLED_uint8SetLEDValue_ValidInputsForwardConnection);
    RUN_TEST(UTEST_HLED_uint8SetLEDValue_ValidInputsReverseConnection);

    UNITY_END(); // unit test end
    return 0;
}
