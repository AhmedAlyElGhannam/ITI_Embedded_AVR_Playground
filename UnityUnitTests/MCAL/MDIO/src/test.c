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


/* tests for MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, MDIO_enuPinState_t Copy_enuPinState) */
// invalid port num
void UTEST_MDIO_enuSetPinValue_InvalidPortNum(void)
{
    // defining function arguments
    uint8_t _port = 86;
    uint8_t _pin = MDIO_PIN2;
    uint8_t _val = MDIO_PIN_HIGH;

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinValue(_port, _pin, _val);

    // return status should be MDIO_INVALID_PORT
    TEST_ASSERT_EQUAL(MDIO_INVALID_PORT, _status);
}
// invalid pin num
void UTEST_MDIO_enuSetPinValue_InvalidPinNum(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTC;
    uint8_t _pin = 42;
    uint8_t _val = MDIO_PIN_HIGH;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);
    
    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinValue(_port, _pin, _val);

    // return status should be MDIO_INVALID_PIN
    TEST_ASSERT_EQUAL(MDIO_INVALID_PIN, _status);

    // make sure nothing was written on PORT
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->PORT);
}
// invalid pin config
void UTEST_MDIO_enuSetPinValue_InvalidPinVal(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTC;
    uint8_t _pin = MDIO_PIN6;
    uint8_t _val = 255;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);
    
    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinValue(_port, _pin, _val);

    // return status should be MDIO_INVALID_PARAM
    TEST_ASSERT_EQUAL(MDIO_INVALID_PARAM, _status);

    // make sure nothing was written on PORT
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->PORT);
}
// using valid inputs
void UTEST_MDIO_enuSetPinValue_ValidInputs(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTB;
    uint8_t _pin = MDIO_PIN3;
    uint8_t _val = MDIO_PIN_HIGH;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);
    
    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPinValue(_port, _pin, _val);

    // return status should be MDIO_OK
    TEST_ASSERT_EQUAL(MDIO_OK, _status);

    // checking value in register to see if it was set correctly
    TEST_ASSERT_EQUAL(0x01, GET_BIT(_portBaseAdd->PORT, _pin));
}

/* tests for MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState) */
// invalid port num
void UTEST_MDIO_enuSetPortValue_InvalidPortNum(void)
{
    // defining function arguments
    uint8_t _port = 242;
    uint8_t _val = MDIO_PORT_HIGH;

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPortValue(_port, _val);

    // return status should be MDIO_INVALID_PORT
    TEST_ASSERT_EQUAL(MDIO_INVALID_PORT, _status);
}
// invalid port config
void UTEST_MDIO_enuSetPortValue_InvalidPortVal(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTA;
    uint8_t _val = 106;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);
    
    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPortValue(_port, _val);

    // return status should be MDIO_INVALID_PARAM
    TEST_ASSERT_EQUAL(MDIO_INVALID_PARAM, _status);

    // make sure nothing was written on PORT
    TEST_ASSERT_EQUAL(0x00, _portBaseAdd->PORT);
}
// using valid inputs
void UTEST_MDIO_enuSetPortValue_ValidInputs(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTA;
    uint8_t _val = MDIO_PORT_HIGH;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);
    
    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuSetPortValue(_port, _val);

    // return status should be MDIO_OK
    TEST_ASSERT_EQUAL(MDIO_OK, _status);

    // checking value in register to see if it was set correctly
    TEST_ASSERT_EQUAL(MDIO_PORT_HIGH, _portBaseAdd->PORT);
}

/* tests for MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum, uint8_t* Add_uint8PtrPinValue) */
// invalid port num
void UTEST_MDIO_enuGetPinValue_InvalidPortNum(void)
{
    // defining function arguments
    uint8_t _port = 83;
    uint8_t _pin = MDIO_PIN3;
    uint8_t _val;

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuGetPinValue(_port, _pin, &_val);

    // return status should be MDIO_INVALID_PORT
    TEST_ASSERT_EQUAL(MDIO_INVALID_PORT, _status);
}
// invalid pin num
void UTEST_MDIO_enuGetPinValue_InvalidPinNum(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTD;
    uint8_t _pin = 90;
    uint8_t _val;

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuGetPinValue(_port, _pin, &_val);

    // return status should be MDIO_INVALID_PIN
    TEST_ASSERT_EQUAL(MDIO_INVALID_PIN, _status);
}
// invalid ptr
void UTEST_MDIO_enuGetPinValue_InvalidPtr(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTB;
    uint8_t _pin = MDIO_PIN3;

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuGetPinValue(_port, _pin, NULL);

    // return status should be MDIO_NULL_PTR
    TEST_ASSERT_EQUAL(MDIO_NULL_PTR, _status);
}
// using valid inputs
void UTEST_MDIO_enuGetPinValue_ValidInputs(void)
{
    // defining function arguments
    uint8_t _port = MDIO_PORTB;
    uint8_t _pin = MDIO_PIN3;
    uint8_t _val;
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(_port);
    
    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // writing a dummy value in PINNx to check if it was read correctly
    SET_BIT(_portBaseAdd->PIN, MDIO_PIN3);

    // calling function with right arguments
    MDIO_enuErrorStatus_t _status = MDIO_enuGetPinValue(_port, _pin, &_val);

    // return status should be MDIO_OK
    TEST_ASSERT_EQUAL(MDIO_OK, _status);

    // checking value in register to see if it was read correctly
    TEST_ASSERT_EQUAL(_val, GET_BIT(_portBaseAdd->PIN, _pin));
}
