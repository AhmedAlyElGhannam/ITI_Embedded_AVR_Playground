#include "test.h"


int main(void)
{
    UNITY_BEGIN(); // unit test beginning

    // MDIO_enuSetPinConfigration tests
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_InvalidPortNum);
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_InvalidPinNum);
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_InvalidPinConfig);
    RUN_TEST(UTEST_MDIO_enuSetPinConfigration_ValidInputs);

    // MDIO_enuSetPortConfigration tests
    RUN_TEST(UTEST_MDIO_enuSetPortConfigration_InvalidPortNum);
    RUN_TEST(UTEST_MDIO_enuSetPortConfigration_InvalidPortConfig);
    RUN_TEST(UTEST_MDIO_enuSetPortConfigration_ValidInputs);

    // MDIO_enuSetPinValue tests
    RUN_TEST(UTEST_MDIO_enuSetPinValue_InvalidPortNum);
    RUN_TEST(UTEST_MDIO_enuSetPinValue_InvalidPinNum);
    RUN_TEST(UTEST_MDIO_enuSetPinValue_InvalidPinVal);
    RUN_TEST(UTEST_MDIO_enuSetPinValue_ValidInputs);

    // MDIO_enuSetPortValue tests
    RUN_TEST(UTEST_MDIO_enuSetPortValue_InvalidPortNum);
    RUN_TEST(UTEST_MDIO_enuSetPortValue_InvalidPortVal);
    RUN_TEST(UTEST_MDIO_enuSetPortValue_ValidInputs);

    // MDIO_enuGetPinValue tests
    RUN_TEST(UTEST_MDIO_enuGetPinValue_InvalidPortNum);
    RUN_TEST(UTEST_MDIO_enuGetPinValue_InvalidPinNum);
    RUN_TEST(UTEST_MDIO_enuGetPinValue_InvalidPtr);
    RUN_TEST(UTEST_MDIO_enuGetPinValue_ValidInputs);

    UNITY_END(); // unit test end
    return 0;
}
