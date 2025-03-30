#include "std_types.h"
#include "bit_math.h"
#include "MGIE.h"
#include "MUSART_Registers.h"
#include "MUSART.h"

#define MUSART_TIMEOUT  1000

extern MGIE_CallBackFunction_t MGIE_CallBackFunctions[MGIE_NUM_OF_INTERRUPTS];
extern MUSART_structConfig_t MUSART_structConfig;

static void MUSART_voidToggleTxOnOff(MUSART_enuToggle_t copy_enuState);
static void MUSART_voidToggleRxOnOff(MUSART_enuToggle_t copy_enuState);
static void MUSART_voidToggleTxCompleteIntOnOff(MUSART_enuToggle_t copy_enuState);
static void MUSART_voidToggleRxCompleteIntOnOff(MUSART_enuToggle_t copy_enuState);
static void MUSART_voidSetOperationMode(MUSART_enuOpMode_t copy_enuOpMode);
static void MUSART_voidConfigFrameSettings(MUSART_enuNumOfDataBits_t copy_enuDataLen, MUSART_enuParityMode_t copy_enuParityMode, MUSART_enuNumOfStopBits_t copy_enuNumOfStopBits);
static void MUSART_voidSetBaudRate(MUSART_enuBaudRate_t copy_enuBaudRate, MUSART_enuSpeed_t copy_enuSpeed);


MUSART_enuErrorStatus_t MUSART_enuInit(void)
{
    MUSART_enuErrorStatus_t ret_enuErrorStatus = MUSART_ALL_OK;
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;

    if ((MUSART_structConfig.baudRate > USART_BAUD_115200) || (MUSART_structConfig.baudRate < USART_BAUD_2400))
    {
        ret_enuErrorStatus = MUSART_BAUD_RATE;
    }
    else if (MUSART_structConfig.dataBits > USART_DATA_BITS_9)
    {
        ret_enuErrorStatus = MUSART_INV_DATA_LEN;
    }
    else if (MUSART_structConfig.mode > USART_MODE_SYNC)
    {
        ret_enuErrorStatus = MUSART_INV_OP_MODE;
    }
    else if (MUSART_structConfig.parity > USART_PARITY_ODD)
    {
        ret_enuErrorStatus = MUSART_INV_PARITY;
    }
    else if (MUSART_structConfig.speed > USART_SPEED_DOUBLE)
    {
        ret_enuErrorStatus = MUSART_INV_SPEED;
    }
    else if (MUSART_structConfig.stopBits > USART_STOP_BITS_2)
    {
        ret_enuErrorStatus = MUSART_INV_NUM_OF_STOP_BITS;
    }
    else 
    {
        MUSART_voidSetBaudRate(MUSART_structConfig.baudRate, MUSART_structConfig.speed);

        MUSART_voidConfigFrameSettings(MUSART_structConfig.dataBits, MUSART_structConfig.parity, MUSART_structConfig.stopBits);

        MUSART_voidSetOperationMode(MUSART_structConfig.mode);

        MUSART_voidToggleTxCompleteIntOnOff(MUSART_ENABLE);
        MUSART_voidToggleRxCompleteIntOnOff(MUSART_ENABLE);

        MUSART_voidToggleTxOnOff(MUSART_ENABLE);
        MUSART_voidToggleRxOnOff(MUSART_ENABLE);
    }

    return ret_enuErrorStatus;
}

static void MUSART_voidToggleTxOnOff(MUSART_enuToggle_t copy_enuState)
{
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;

    USART->UCSRB |= (copy_enuState << 3); /*TXEN*/
}

static void MUSART_voidToggleRxOnOff(MUSART_enuToggle_t copy_enuState)
{
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;

    USART->UCSRB |= (copy_enuState << 4); /*RXEN*/
}

static void MUSART_voidToggleTxCompleteIntOnOff(MUSART_enuToggle_t copy_enuState)
{
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;

    USART->UCSRB |= (copy_enuState << 6); /*TXCIE*/
}

static void MUSART_voidToggleRxCompleteIntOnOff(MUSART_enuToggle_t copy_enuState)
{
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;

    USART->UCSRB |= (copy_enuState << 7); /*RXCIE*/
}

static void MUSART_voidSetOperationMode(MUSART_enuOpMode_t copy_enuOpMode)
{
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;

    /* select UCSRC register */
    SET_BIT(USART->UBRRH_UCSRC, 7); /*set URSEL*/

    /* set mode */
    USART->UBRRH_UCSRC |= (copy_enuOpMode << 6);
}

static void MUSART_voidConfigFrameSettings(MUSART_enuNumOfDataBits_t copy_enuDataLen, MUSART_enuParityMode_t copy_enuParityMode, MUSART_enuNumOfStopBits_t copy_enuNumOfStopBits)
{
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;
	uint32_t local_uint32UCSRCTemp = 0x80; /* to make sure URSEL is not overwritten */

    /* select UCSRC register */
    SET_BIT(USART->UBRRH_UCSRC, 7); /*set URSEL*/

    /* data len */
    local_uint32UCSRCTemp |= ((copy_enuDataLen & 0b11) << 1);
    USART->UCSRB |= ((copy_enuDataLen & 0b100));

    /* parity mode */
    local_uint32UCSRCTemp |= (copy_enuParityMode << 4);

    /* stop bits */
    local_uint32UCSRCTemp |= (copy_enuNumOfStopBits << 3);

    /* set temp value into UCSRC */
	USART->UBRRH_UCSRC = local_uint32UCSRCTemp;
}

static void MUSART_voidSetBaudRate(MUSART_enuBaudRate_t copy_enuBaudRate, MUSART_enuSpeed_t copy_enuSpeed)
{
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;
	uint32_t local_uint32UBRRTemp = 0x00;

    local_uint32UBRRTemp = ((F_CPU / (copy_enuSpeed * 8UL)) / copy_enuBaudRate) - 1;
    
    if (copy_enuSpeed == USART_SPEED_NORMAL)
    {
        CLR_BIT(USART->UCSRA, 1); /*U2X bit*/
    }
    else if (copy_enuSpeed == USART_SPEED_DOUBLE)
    {
        SET_BIT(USART->UCSRA, 1); /*U2X bit*/
    }
    else {}

    /* select UBRRH register */
    CLR_BIT(USART->UBRRH_UCSRC, 7); /*clear URSEL*/

	USART->UBRRH_UCSRC = (uint8_t)((local_uint32UBRRTemp >> 8) & 0xFF);
    USART->UBRRL = (uint8_t)(local_uint32UBRRTemp & 0xFF);
}

MUSART_enuErrorStatus_t MUSART_enuSetUSARTCallBack(MGIE_CallBackFunction_t ptr_CBF, MUSART_enuIRQSource_t copy_enuIRQSrc)
{
    MUSART_enuErrorStatus_t ret_enuErrorStatus = MUSART_ALL_OK;

    if (ptr_CBF == NULL)
    {
        ret_enuErrorStatus = MUSART_NULL_PTR;
    }
    else if (copy_enuIRQSrc > MUSART_RX_IRQ)
    {
        ret_enuErrorStatus = MUSART_INV_IRQ_SRC;
    }
    else 
    {
        volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;

        switch (copy_enuIRQSrc)
        {
            case MUSART_TX_IRQ:
                MGIE_CallBackFunctions[MGIE_USART_TX_COMPLETE] = ptr_CBF;
            break;

            case MUSART_RX_IRQ:
                MGIE_CallBackFunctions[MGIE_USART_RX_COMPLETE] = ptr_CBF;
            break;
        }
    }

    return ret_enuErrorStatus;
}

MUSART_enuErrorStatus_t MUSART_enuSendDataSync(uint8_t copy_uint8Data)
{
    MUSART_enuErrorStatus_t ret_enuErrorStatus = MUSART_ALL_OK;
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;
    uint32_t local_uint32Timeout = MUSART_TIMEOUT;

	/**wait for empty transmit buffer*/
	while ((GET_BIT(USART->UCSRA, 5) == 0) && (--local_uint32Timeout));

    if ((local_uint32Timeout == 0) && (GET_BIT(USART->UCSRA, 5) == 0))
    {
        ret_enuErrorStatus = MUSART_TX_TIMEOUT;
    }
    else 
    {
        /**put data in buffer*/
        USART->UDR = copy_uint8Data;
    }

    return ret_enuErrorStatus;
}

MUSART_enuErrorStatus_t MUSART_enuReceiveDataSync(uint8_t* ptr_uint8Data)
{
    MUSART_enuErrorStatus_t ret_enuErrorStatus = MUSART_ALL_OK;
    volatile MUSART_Registers_t* USART = (volatile MUSART_Registers_t*)MUSART_BASE_ADDRESS;
    uint32_t local_uint32Timeout = MUSART_TIMEOUT;

	/**wait for data to be received*/
	while ((GET_BIT(USART->UCSRA, 7) == 0) && (--local_uint32Timeout));

    if ((local_uint32Timeout == 0) && (GET_BIT(USART->UCSRA, 5) == 0))
    {
        ret_enuErrorStatus = MUSART_TX_TIMEOUT;
    }
    else if (ptr_uint8Data == NULL)
    {
        ret_enuErrorStatus = MUSART_NULL_PTR;
    }
    else 
    {
        /**put data in buffer*/
        (*ptr_uint8Data) = USART->UDR;
    }

    return ret_enuErrorStatus;
}

void __vector_13 (void)		__attribute__ ((signal)) ;
void __vector_13 (void)
{
	if (MGIE_CallBackFunctions[MGIE_USART_RX_COMPLETE] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_USART_RX_COMPLETE]();
    }
    else {}
}

void __vector_15 (void)		__attribute__ ((signal)) ;
void __vector_15 (void)
{
    if (MGIE_CallBackFunctions[MGIE_USART_TX_COMPLETE] != NULL)
    {
        MGIE_CallBackFunctions[MGIE_USART_TX_COMPLETE]();
    }
    else {}
}