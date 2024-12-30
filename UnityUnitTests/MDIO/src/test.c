#include "test.h"


// defining 4 pointers to reg structs instead of using actual base addresses during tests
MDIO_strPortRegElement_t MOCK_PORTA = {0x00, 0x00, 0x00};
MDIO_strPortRegElement_t MOCK_PORTB = {0x00, 0x00, 0x00};
MDIO_strPortRegElement_t MOCK_PORTC = {0x00, 0x00, 0x00};
MDIO_strPortRegElement_t MOCK_PORTD = {0x00, 0x00, 0x00};

// macro to initialize all port registers to 0
#define INITIALIZE_PORT_REGS_TO_ZEROS(PORT_BASE_ADD)    \
                    do                                  \
                    {                                   \
                        (PORT_BASE_ADD)->DDR = 0x00;    \
                        (PORT_BASE_ADD)->PIN = 0x00;    \
                        (PORT_BASE_ADD)->PORT = 0x00;   \
                    } while (false) 


// function that runs at the beginning of tests
void setUp(void)
{

}

// function that runs at the end of tests
void tearDown(void)
{

}


/* tests for MDIO_enuErrorStatus_t MDIO_enuSetPinConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinConfig_t Copy_enuPinConfig) */
// invalid port num
void UTEST_MDIO_enuSetPinConfigration_InvalidPortNum(void)
{
    // defining function arguments
    uint8_t _port = '0';
    uint8_t _pin = MDIO_PIN7;
    uint8_t _config = MDIO_PIN_OUTPUT;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(MDIO_PORTD);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinConfigration(_port, _pin, _config);

    // return status should be MDIO_INVALID_PARAM
    TEST_ASSERT_EQUAL(MDIO_INVALID_PORT, _status);

    // make sure nothing was written on DDR
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->DDR);
}
// invalid pin num
void UTEST_MDIO_enuSetPinConfigration_InvalidPinNum(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTB;
    uint8_t _pin = 42;
    uint8_t _config = MDIO_PIN_OUTPUT;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(MDIO_PORTD);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinConfigration(_port, _pin, _config);

    // return status should be MDIO_INVALID_PARAM
    TEST_ASSERT_EQUAL(MDIO_INVALID_PIN, _status);

    // make sure nothing was written on DDR
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->DDR);
}
// invalid pin config
void UTEST_MDIO_enuSetPinConfigration_InvalidPinConfig(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTC;
    uint8_t _pin = MDIO_PIN3;
    uint8_t _config = 'C';
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(MDIO_PORTD);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinConfigration(_port, _pin, _config);

    // return status should be MDIO_INVALID_PARAM
    TEST_ASSERT_EQUAL(MDIO_INVALID_PARAM, _status);

    // make sure nothing was written on DDR
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->DDR);
}
// using valid inputs
void UTEST_MDIO_enuSetPinConfigration_ValidInputs(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTD;
    uint8_t _pin = MDIO_PIN5;
    uint8_t _config = MDIO_PIN_OUTPUT;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(MDIO_PORTD);
    
    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinConfigration(_port, _pin, _config);

    // return status should be MDIO_OK
    TEST_ASSERT_EQUAL(MDIO_OK, _status);

    // checking value in register to see if it was set correctly
    TEST_ASSERT_EQUAL(0x01, GET_BIT(_portBaseAdd->DDR, _pin));
}

// /* tests for MDIO_enuErrorStatus_t MDIO_enuSetPortConfigration(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortConfig_t Copy_enuPortConfig) */
// // invalid port num
// void UTEST_MDIO_enuSetPortConfigration_InvalidPortNum(void)
// {

// }
// // invalid port config
// void UTEST_MDIO_enuSetPortConfigration_InvalidPortConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuSetPortConfigration_ValidInputs(void);

// /* tests for MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuPinState) */
// // invalid port num
// void UTEST_MDIO_enuSetPinValue_InvalidPortNum(void);
// // invalid pin num
// void UTEST_MDIO_enuSetPinValue_InvalidPinNum(void);
// // invalid pin config
// void UTEST_MDIO_enuSetPinValue_InvalidPinConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuSetPinValue_ValidInputs(void);

// /* tests for MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState) */
// // invalid port num
// void UTEST_MDIO_enuSetPortValue_InvalidPortNum(void);
// // invalid port config
// void UTEST_MDIO_enuSetPortValue_InvalidPortConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuSetPortValue_ValidInputs(void);

// /* tests for MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, uint8_t* Add_uint8PtrPinValue) */
// // invalid port num
// void UTEST_MDIO_enuGetPinValue_InvalidPortNum(void);
// // invalid pin num
// void UTEST_MDIO_enuGetPinValue_InvalidPinNum(void);
// // invalid pin config
// void UTEST_MDIO_enuGetPinValue_InvalidPinConfig(void);
// // using valid inputs
// void UTEST_MDIO_enuGetPinValue_ValidInputs(void);
