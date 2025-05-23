#define F_CPU 	8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define TRUE 1

#define SET_BIT(X, POS) (X |= (0x01 << POS))
#define CLR_BIT(X, POS) (X &= ~(0x01 << POS))
#define TOG_BIT(X, POS) (X ^= (0x01 << POS))
#define GET_BIT(X, POS) ((X >> POS) & 0x01)

void main(void)
{
	SET_BIT(DDRA, 0);
	
	while (TRUE)
	{
		TOG_BIT(PORTA, 0);
		_delay_ms(500);
	}
}


