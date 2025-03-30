#ifndef MUSART_H
#define MUSART_H

typedef enum 
{
    MUSART_ALL_OK,
    MUSART_NULL_PTR,
    MUSART_INV_IRQ_SRC,
    MUSART_BAUD_RATE,
    MUSART_INV_DATA_LEN,
    MUSART_INV_OP_MODE,
    MUSART_INV_PARITY,
    MUSART_INV_SPEED,
    MUSART_INV_NUM_OF_STOP_BITS,
    MUSART_TX_TIMEOUT,
    MUSART_RX_TIMEOUT,
} MUSART_enuErrorStatus_t;

typedef enum
{
    USART_BAUD_2400 = 2400,    ///< 2400 baud
    USART_BAUD_9600 = 9600,    ///< 9600 baud
    USART_BAUD_19200 = 19200,  ///< 19200 baud
    USART_BAUD_38400 = 38400,  ///< 38400 baud
    USART_BAUD_57600 = 57600,  ///< 57600 baud
    USART_BAUD_115200 = 115200 ///< 115200 baud
} MUSART_enuBaudRate_t;

typedef enum
{
    USART_PARITY_NONE = 0b00, ///< No parity
    USART_PARITY_EVEN = 0b10, ///< Even parity
    USART_PARITY_ODD = 0b11,   ///< Odd parity
} MUSART_enuParityMode_t;

typedef enum
{
    USART_STOP_BITS_1 = 0U, ///< 1 stop bit
    USART_STOP_BITS_2 = !USART_STOP_BITS_1, ///< 2 stop bits
} MUSART_enuNumOfStopBits_t;

typedef enum
{
    USART_DATA_BITS_5 = 0b000, ///< 5 data bits
    USART_DATA_BITS_6 = 0b001, ///< 6 data bits
    USART_DATA_BITS_7 = 0b010, ///< 7 data bits
    USART_DATA_BITS_8 = 0b011, ///< 8 data bits
    USART_DATA_BITS_9 = 0b111,  ///< 9 data bits
} MUSART_enuNumOfDataBits_t;

typedef enum
{
    USART_MODE_ASYNC = 0U, ///< Asynchronous operation
    USART_MODE_SYNC = !USART_MODE_ASYNC,  ///< Synchronous operation
} MUSART_enuOpMode_t;

typedef enum
{
    USART_SPEED_NORMAL = 2U, 
    USART_SPEED_DOUBLE = 1U,  
} MUSART_enuSpeed_t;

typedef enum 
{
    MUSART_TX_IRQ,
    MUSART_RX_IRQ,
} MUSART_enuIRQSource_t;

typedef enum 
{
    MUSART_ENABLE = 1U,
    MUSART_DISABLE = !MUSART_ENABLE,
} MUSART_enuToggle_t;

typedef struct
{
    MUSART_enuBaudRate_t baudRate;     
    MUSART_enuParityMode_t parity;        
    MUSART_enuNumOfStopBits_t stopBits;    
    MUSART_enuNumOfDataBits_t dataBits;    
    MUSART_enuOpMode_t mode;             
    MUSART_enuSpeed_t speed;
} MUSART_structConfig_t;

extern MUSART_enuErrorStatus_t MUSART_enuInit(void);
extern MUSART_enuErrorStatus_t MUSART_enuSetUSARTCallBack(MGIE_CallBackFunction_t ptr_CBF, MUSART_enuIRQSource_t copy_enuIRQSrc);
extern MUSART_enuErrorStatus_t MUSART_enuSendDataSync(uint8_t copy_uint8Data);
extern MUSART_enuErrorStatus_t MUSART_enuReceiveDataSync(uint8_t* ptr_uint8Data);

#endif