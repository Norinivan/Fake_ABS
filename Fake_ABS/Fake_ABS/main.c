/*
 * main.c
 *
 * Created: 10/21/2025 11:19:40 PM
 *  Author: user
 */ 

#define F_CPU 1200000UL
#include <xc.h>
#include <util/delay.h>
#define OUTPIN	0
#define BTNPIN	1
#define FUSEPIN	4

void blink(void);

int main(void)
{
	DDRB|=(1<<OUTPIN);
	
	//-----------Start Blink-----------
	_delay_ms(500);
	PORTB|=(1<<OUTPIN);
	_delay_ms(1500);
	PORTB&=~(1<<OUTPIN);
	//---------------------------------
	
    while(1)
    {
        blink();
		_delay_ms(10000);
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
	}
	PORTB^=(1<<OUTPIN);
}
}