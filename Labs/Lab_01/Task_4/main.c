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

#define BIT_0	0
#define BIT_1	1	
#define BIT_2	2
#define BIT_3	3
#define BTN	7

void main(void)
{
	volatile unsigned char counter = 0;
	
	// set counter pins to output
	SET_BIT(DDRA, BIT_0);
	SET_BIT(DDRA, BIT_1);
	SET_BIT(DDRA, BIT_2);
	SET_BIT(DDRA, BIT_3);

	// set button pin to input (BTN)
	CLR_BIT(DDRA, BTN);

	// clear all counter pins to initialize it
	PORTA = 0x00;
	
	while (TRUE)
	{
		_delay_ms(250);
		if (GET_BIT(PINA, BTN) == HIGH)
		{
			_delay_ms(150);
			if (GET_BIT(PINA, BTN) == HIGH)
			{
				counter += 1;
				if (counter == 0x10)
				{
					PORTA = 0x00;
					counter = 0x00;
					continue;
				}
				PORTA = counter;
			}
			_delay_ms(50);
		}
	}
}


