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


// function that runs at the beginning of tests (must be defined for unity)
void setUp(void)
{

}

// function that runs at the end of tests (must be defined for unity)
void tearDown(void)
{

}


// /* only one test for void MPORT_voidInit(void) */
// void UTEST_MPORT_voidInit_ValidEntriesInArr(void)
// {

// }

/* tests for MPORT_enuErrorStatus_t MPORT_enuSetPinDirection(MPORT_enuPortPin_t Copy_enuPortPinNum,  MPORT_enuPortPinDir_t  Copy_enuPortPinDir) */
// wrong port pin format
void UTEST_MPORT_enuSetPinDirection_InvalidPortPinNum(void)
{
    // defining function arguments
    uint8_t _portpin = 89;
    uint8_t _dir = MPORT_PORT_PIN_OUTPUT;
    uint8_t _port = GET_HIGH_NIB(_portpin);
    uint8_t _pin = GET_LOW_NIB(_portpin);

    // calling function with right arguments
    MPORT_enuErrorStatus_t _status = MPORT_enuSetPinDirection(_portpin, _dir);

    // return status should be MPORT_ERROR_INVALID_PIN
    TEST_ASSERT_EQUAL(MPORT_ERROR_INVALID_PIN, _status);
}
// wrong port pin direction
void UTEST_MPORT_enuSetPinDirection_InvalidPortPinDir(void)
{
    // defining function arguments
    uint8_t _portpin = MPORT_PIN_B7;
    uint8_t _dir = 'd';
    uint8_t _port = GET_HIGH_NIB(_portpin);
    uint8_t _pin = GET_LOW_NIB(_portpin);
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MPORT_enuErrorStatus_t _status = MPORT_enuSetPinDirection(_portpin, _dir);

    // return status should be MPORT_ERROR_INVALID_DIRECTION
    TEST_ASSERT_EQUAL(MPORT_ERROR_INVALID_DIRECTION, _status);

    // make sure nothing was written on DDR
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->DDR);
}
// valid inputs
void UTEST_MPORT_enuSetPinDirection_ValidInputs(void)
{
    // defining function arguments
    uint8_t _portpin = MPORT_PIN_B7;
    uint8_t _dir = MPORT_PORT_PIN_OUTPUT;
    uint8_t _port = GET_HIGH_NIB(_portpin);
    uint8_t _pin = GET_LOW_NIB(_portpin);
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MPORT_enuErrorStatus_t _status = MPORT_enuSetPinDirection(_portpin, _dir);

    // return status should be MPORT_OK
    TEST_ASSERT_EQUAL(MPORT_OK, _status);

    // make sure right bit was written successfully
    TEST_ASSERT_EQUAL(0x01, GET_BIT(_portBaseAdd->DDR, _pin));
}

/* tests for MPORT_enuErrorStatus_t MPORT_enuSetPinMode(MPORT_enuPortPin_t Copy_enuPortPinNum, MPORT_enuPortPinMode_t Copy_enuPortPinMode) */
// wrong port pin format
void UTEST_MPORT_enuSetPinMode_InvalidPortPinNum(void)
{
    // defining function arguments
    uint8_t _portpin = 15;
    uint8_t _mode = MPORT_PIN_MODE_INPUT_PULLUP;
    uint8_t _port = GET_HIGH_NIB(_portpin);
    uint8_t _pin = GET_LOW_NIB(_portpin);

    // calling function with right arguments
    MPORT_enuErrorStatus_t _status = MPORT_enuSetPinMode(_portpin, _mode);

    // return status should be MPORT_ERROR_INVALID_PIN
    TEST_ASSERT_EQUAL(MPORT_ERROR_INVALID_PIN, _status);
}
// wrong port pin direction
void UTEST_MPORT_enuSetPinMode_InvalidPortPinMode(void)
{
    // defining function arguments
    uint8_t _portpin = MPORT_PIN_D5;
    uint8_t _mode = 'f';
    uint8_t _port = GET_HIGH_NIB(_portpin);
    uint8_t _pin = GET_LOW_NIB(_portpin);
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MPORT_enuErrorStatus_t _status = MPORT_enuSetPinMode(_portpin, _mode);

    // return status should be MPORT_ERROR_INVALID_MODE
    TEST_ASSERT_EQUAL(MPORT_ERROR_INVALID_MODE, _status);

    // make sure nothing was written on PORT
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->PORT);
}
// valid inputs
void UTEST_MPORT_enuSetPinMode_ValidInputs(void)
{
    // defining function arguments
    uint8_t _portpin = MPORT_PIN_D5;
    uint8_t _mode = MPORT_PIN_MODE_INPUT_PULLUP;
    uint8_t _port = GET_HIGH_NIB(_portpin);
    uint8_t _pin = GET_LOW_NIB(_portpin);
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MPORT_enuErrorStatus_t _status = MPORT_enuSetPinMode(_portpin, _mode);

    // return status should be MPORT_OK
    TEST_ASSERT_EQUAL(MPORT_OK, _status);

    // make sure right bit was written successfully
    TEST_ASSERT_EQUAL(0x01, GET_BIT(_portBaseAdd->PORT, _pin));
}

