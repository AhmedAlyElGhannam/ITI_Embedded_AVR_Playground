#include "std_types.h"
#include "bit_math.h"
#include "MGIE.h"
#include "MUSART_Registers.h"
#include "MUSART.h"

MUSART_structConfig_t MUSART_structConfig = 
{
    .baudRate = USART_BAUD_9600,
    .dataBits = USART_DATA_BITS_8,
    .mode = USART_MODE_ASYNC,
    .parity = USART_PARITY_NONE,
    .speed = USART_SPEED_NORMAL,
    .stopBits = USART_STOP_BITS_1
};