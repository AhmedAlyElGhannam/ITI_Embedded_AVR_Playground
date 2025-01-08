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

extern HLED_structLEDConfig_t Global_HLED_structLEDConfigArr[NUM_OF_LEDS];

// function that runs at the beginning of tests (must be defined for unity)
void setUp(void)
{

}

// function that runs at the end of tests (must be defined for unity)
void tearDown(void)
{

}

/*void UTEST_HLED_voidInit_ValidEntriesInArr(void)
{
    // defining iterator for looping over defined LEDs
    uint8_t _iter;

    // defining variable to hold base register address
    MDIO_strPortRegElement_t* _portBaseAdd;
    
    // calling init function (takes no arguments)
    HLED_voidInit();

    // seeing if DDR bits corresponding to LED pins were set
    for (_iter = FIRST_LED; _iter < NUM_OF_LEDS; _iter++)
    {
        _portBaseAdd = MDIO_GET_PORT_ADD(Global_HLED_structLEDConfigArr[_iter].portNum);
        TEST_ASSERT_EQUAL(0x01, GET_BIT(_portBaseAdd->DDR, Global_HLED_structLEDConfigArr[_iter].pinNum));
    }
}*/

/* HLED_enuErrorStatus_t HLED_uint8SetLEDValue(uint8_t Copy_uint8LEDName, HLED_enuLEDValue_t Copy_uint8LEDValue) */
void UTEST_HLED_uint8SetLEDValue_InvalidLEDName(void)
{
    // defining function arguments
    uint8_t _ledName = 5;
    uint8_t _val = HLED_ON;

    // calling function with right arguments
    HLED_enuErrorStatus_t _status = HLED_uint8SetLEDValue(_ledName, _val);

    // return status should be HLED_INVALID_LED_NAME
    TEST_ASSERT_EQUAL(HLED_INVALID_LED_NAME, _status);
}

void UTEST_HLED_uint8SetLEDValue_InvalidLEDValue(void)
{
    // defining function arguments
    uint8_t _ledName = HLED_ALERT;
    uint8_t _val = 15;

    // calling function with right arguments
    HLED_enuErrorStatus_t _status = HLED_uint8SetLEDValue(_ledName, _val);

    // return status should be HLED_INVALID_LED_VALUE
    TEST_ASSERT_EQUAL(HLED_INVALID_LED_VALUE, _status);
}
void UTEST_HLED_uint8SetLEDValue_ValidInputsForwardConnection(void)
{
    // defining function arguments
    uint8_t _ledName = HLED_ALERT;
    uint8_t _val = HLED_ON;

    // calculating case address of port LED is connected to
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(Global_HLED_structLEDConfigArr[HLED_ALERT].portNum);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // modifying HLED_ALERT connection to forward
    Global_HLED_structLEDConfigArr[HLED_ALERT].connection = HLED_FORWARD;

    // calling function with right arguments
    HLED_enuErrorStatus_t _status = HLED_uint8SetLEDValue(_ledName, _val);

    // return status should be HLED_OK
    TEST_ASSERT_EQUAL(HLED_OK, _status);

    // HLED_ON should correspond to a set bit in PORT register
    TEST_ASSERT_EQUAL(0x01, GET_BIT(_portBaseAdd->PORT, Global_HLED_structLEDConfigArr[HLED_ALERT].pinNum));
}

void UTEST_HLED_uint8SetLEDValue_ValidInputsReverseConnection(void)
{
    // defining function arguments
    uint8_t _ledName = HLED_ALERT;
    uint8_t _val = HLED_ON;

    // calculating case address of port LED is connected to
    MDIO_strPortRegElement_t* _portBaseAdd = MDIO_GET_PORT_ADD(Global_HLED_structLEDConfigArr[HLED_ALERT].portNum);

    // initializing port registers to zeros
    INITIALIZE_PORT_REGS_TO_ZEROS(_portBaseAdd);

    // modifying HLED_ALERT connection to forward
    Global_HLED_structLEDConfigArr[HLED_ALERT].connection = HLED_REVERSE;

    // calling function with right arguments
    HLED_enuErrorStatus_t _status = HLED_uint8SetLEDValue(_ledName, _val);

    // return status should be HLED_OK
    TEST_ASSERT_EQUAL(HLED_OK, _status);

    // HLED_ON should correspond to a cleared bit in PORT register
    TEST_ASSERT_EQUAL(0x00, GET_BIT(_portBaseAdd->PORT, Global_HLED_structLEDConfigArr[HLED_ALERT].pinNum));
}
