/*
 * 4ADCs.c
 *
 * Created: 17.09.2019 10:07:43
 * Author : Neuer Besitzer
 */ 

#include <avr/io.h>


int adc_1;
int adc_2;
int adc_3;
int adc_4;

int ADC_read() //ADMUX um channel zu wählen noch ändern
{
	ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));  // A0 pin//Enables ADC
	ADCSRA |= (1<<ADSC);
	while(ADCSRA &(1<<ADSC));
	adc_1 = ADC;
	
	ADMUX |= (1<<MUX0);  // A1 pin//Enables ADC
	ADCSRA |= (1<<ADSC);
	while(ADCSRA &(1<<ADSC));
	adc_2 = ADC;

	ADMUX |= (1<<MUX1); // A2 pin//Enables ADC
	ADMUX &= ~(1<<MUX0);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA &(1<<ADSC));
	adc_3 = ADC;

	ADMUX |= ((1<<MUX1)|(1<<MUX0));  // A3 pin//Enables ADC
	ADCSRA |= (1<<ADSC);
	while(ADCSRA &(1<<ADSC));
	adc_4 = ADC;
	
	return adc_1, adc_2, adc_3, adc_4;
}

void main()
{
	DDRD |= 0xFF;
	ADMUX |= ((1<<REFS0)|(1<<REFS1));
	ADCSRA |= 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;       //Sets ADC Prescalar as 128, i.e. my ADC frequency is 125KHz
	ADCSRA |= 1<<ADEN;
	//Serial.begin(9600);
	ADC_read;
}
