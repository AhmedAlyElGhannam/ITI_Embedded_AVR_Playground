#define F_CPU 	8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define TRUE 	1
#define HIGH 	1
#define LOW 	0

#define SET_BIT(X, POS) (X |= (0x01 << POS))
#define CLR_BIT(X, POS) (X &= ~(0x01 << POS))
#define TOG_BIT(X, POS) (X ^= (0x01 << POS))
#define GET_BIT(X, POS) ((X >> POS) & 0x01)

void main(void)
{
	// set pin 0 to output (LED)
	SET_BIT(DDRA, 0);

	// set pin 1 to input (BTN)
	CLR_BIT(DDRA, 7);
	
	while (TRUE)
	{
		if (GET_BIT(PINA, 7) == HIGH)
			SET_BIT(PORTA, 0);
		else if (GET_BIT(PINA, 7) == LOW)
			CLR_BIT(PORTA, 0);

		_delay_ms(100);

	}
}


