/*
 * main.c
 *
 * Created: 10/21/2025 11:19:40 PM
 *  Author: user
 */ 

#define F_CPU 1200000UL
#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define OUTPIN	0
#define BTNPIN	1
#define FUSEPIN	4
unsigned char status_blink = 0;

void blink(void);

ISR(PCINT0_vect)
{
	if (!(PORTB & (1<<BTNPIN)))
	{
		status_blink = 1;
	}
	else
	{
		status_blink = 0;
		PORTB&=~(1<<OUTPIN);
	}
	
}

int main(void)
{
	DDRB|=(1<<OUTPIN);
	PCMSK |= (1 << BTNPIN) | (1 << FUSEPIN);
	GIMSK |= (1 << PCIE);
	sei();
	
	//-----------Start Blink-----------
	_delay_ms(500);
	PORTB|=(1<<OUTPIN);
	_delay_ms(1500);
	PORTB&=~(1<<OUTPIN);
	//---------------------------------
	
    while(1)
    {
        if (status_blink == 1)
        {
			while(!(PORTB & (1<<BTNPIN)))
			{
				PORTB|=(1<<OUTPIN);
			}
			PORTB&=~(1<<OUTPIN);
			status_blink = 0;
			//blink();
        }
    }
}

void blink(void)
{
unsigned int arr[8]={1500, 500, 500, 500, 1500, 500, 500, 500};
PORTB&=~(1<<OUTPIN);	
for(unsigned char i=0; i<8; i++)
{
	for (unsigned int j=arr[i]; j>0; j--)
	{
		_delay_ms(1);
		if (status_blink == 1)
		{
			break;
		}
	}
	PORTB^=(1<<OUTPIN);
	if (status_blink == 1)
	{
		status_blink = 0;
		break;
	}
}
}