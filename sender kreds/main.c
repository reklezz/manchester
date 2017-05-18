#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>

// Prototyper
void initExtInts();

#define DDR   DDRB
#define PORT PORTB
#define PINNR 0
#define BAUD  9600

#define NO_us 80000/BAUD

//--------------------------------------

void initExtInts()
{
	// Enable extern interrupts INT2 og INT3
	EIMSK |= 0b00001100;
}

// 8 data bit, no parity, 1 stop bit
void SendCharSW(char Tegn)
{

	initExtInts();
	// Global interrupt enable
	sei();
	// Main-loop: Toggle LED7 hvert sekund
	
	unsigned char i;
	unsigned char x = Tegn;
	// Start bit
	PORT &= ~(1<<PINNR);
	_delay_us(NO_us);
	// 8 data bits (LSB first)
	for (i = 0; i<8; i++)
	{
		if(x & 0b00000001)
		PORT |= (1<<PINNR);
		else
		PORT &= ~(1<<PINNR);
		_delay_us(NO_us);
		x = x>>1;
	}
	PORT |= (1<<PINNR);
	_delay_us(NO_us);
}

int main(void)
{
	UCSR0B = 0;
	DDR |= (1<<PINNR);

	while(1)
	{
	}
}

// Interrupt service routine for INT3
ISR (INT3_vect)
{
	SendCharSW('a');
}