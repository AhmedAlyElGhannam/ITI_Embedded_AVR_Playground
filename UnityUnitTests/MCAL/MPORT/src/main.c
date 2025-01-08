#include "test.h"

int main(void)
{
    UNITY_BEGIN(); // unit test beginning

    // MPORT_enuSetPinDirection tests
    RUN_TEST(UTEST_MPORT_enuSetPinDirection_InvalidPortPinNum);
    RUN_TEST(UTEST_MPORT_enuSetPinDirection_InvalidPortPinDir);
    RUN_TEST(UTEST_MPORT_enuSetPinDirection_ValidInputs);

    // MPORT_enuSetPinMode tests
    RUN_TEST(UTEST_MPORT_enuSetPinMode_InvalidPortPinNum);
    RUN_TEST(UTEST_MPORT_enuSetPinMode_InvalidPortPinMode);
    RUN_TEST(UTEST_MPORT_enuSetPinMode_ValidInputs);

    UNITY_END(); // unit test end
    return 0;
}
