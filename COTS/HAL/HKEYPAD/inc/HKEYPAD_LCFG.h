#ifndef HKEYPAD_LCFG_H
#define HKEYPAD_LCFG_H


#define HKEYPAD_NO_OF_ROWS      (4)
#define HKEYPAD_NO_OF_COLS      (4)

typedef enum 
{
	KPD_ONE   = 0b10111110,
	KPD_TWO   = 0b10111101,
	KPD_THREE = 0b10111011,
	KPD_FOUR  = 0b11011110,
	KPD_FIVE  = 0b11011101,
	KPD_SIX   = 0b11011011,
	KPD_SEVEN = 0b11101110,
	KPD_EIGHT = 0b11101101,
	KPD_NINE  = 0b11101011,
	KPD_ZERO  = 0b01111101,
	KPD_CLR   = 0b01111110,
	KPD_DIV   = 0b11100111,
	KPD_MUL   = 0b11010111,
	KPD_SUB   = 0b10110111,
	KPD_ADD   = 0b01110111,
	KPD_EQUAL = 0b01111011
} HKEYPAD_enuKeypadButtonCode_t;

#endif