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
#define OUTPIN	0	//����� �� ��������� �� ������
#define BTNPIN	1	//���� ������ �����������
#define FUSEPIN	4	//���� � �������������� ABS
#define TESTPIN 3	//������ �������� ���
unsigned char	status_blink = 0;	//������ ����������� ��������������� ������� 1,1
unsigned int	counter = 0;	//������� �������, �� �������� ������� ��������������� ����
unsigned char	restart = 0;	//���� ������������ �� ���������� ��������������

void start_blink(void);

ISR(PCINT0_vect)
{
	if (!(PINB & (1<<BTNPIN)))	//���� ������ ������ �����������
	{
		status_blink = 1;		//��������� ���� �����������
		counter = 0;			//��������� ������� �������
		PORTB|=(1<<TESTPIN)|(1<<OUTPIN);	//������� ��������� �� ������
		while(!(PINB & (1<<BTNPIN)));		//���, ���� ������ ������
		PORTB&=~((1<<OUTPIN)|(1<<TESTPIN));	//�������� ���������
	}
	if ((PINB & (1<<FUSEPIN)))				//���� �������������� ���������
	{
		PORTB|=(1<<TESTPIN)|(1<<OUTPIN);	//������� ���������
		while ((PINB & (1<<FUSEPIN)));		//���, ���� �� ������� ��������������
		PORTB&=~((1<<OUTPIN)|(1<<TESTPIN));	//�������� ���������
		restart = 1;						//�������� ���� ������������
	}
		
}

int main(void)
{
	{
		
	DDRB|=(1<<OUTPIN)|(1<<TESTPIN);
	PORTB |=(1<<FUSEPIN);
	PCMSK |= (1 << BTNPIN) | (1 << FUSEPIN);
	GIMSK |= (1 << PCIE);
	sei();
	
	if ((PINB & (1<<FUSEPIN)))	
	{
		PORTB|=(1<<TESTPIN)|(1<<OUTPIN);	//������� ���������
		while ((PINB & (1<<FUSEPIN)));		//���, ���� �� ������� ��������������
		PORTB&=~((1<<OUTPIN)|(1<<TESTPIN));
	}
	start_blink();
	
	}
    while(1)
    {
        if (status_blink == 1)
        {
			_delay_ms(10);
			counter++;
			if (counter == 150 || counter == 350 || counter == 850 || counter == 1050)
			{
				PORTB |= (1<<OUTPIN)|(1<<TESTPIN);
			}
			if (counter == 200 || counter == 400 || counter == 900 || counter == 1100)
			{
				PORTB&=~((1<<OUTPIN)|(1<<TESTPIN));
			}
			if (counter == 1100)
			{
				status_blink = 0;
				counter = 0;
			}
        }
		if (restart == 1)
		{
			status_blink = 0;
			counter = 0;
			restart = 0;
			start_blink();
		}
    }
}

void start_blink(void)
{
	_delay_ms(500);
	PORTB|=(1<<OUTPIN);
	_delay_ms(1500);
	PORTB&=~(1<<OUTPIN);
}