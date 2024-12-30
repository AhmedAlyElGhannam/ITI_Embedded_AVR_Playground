#include "test.h"

int main(void)
{
    UNITY_BEGIN(); // unit test beginning

    // MDIO_enuSetPinConfigration tests
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_InvalidPortNum);
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_InvalidPinNum);
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_InvalidPinConfig);
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_ValidInputs);

    UNITY_END(); // unit test end
    return 0;
}