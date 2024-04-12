/*************************************************************
 * Universidad del Valle de Guatemala
 * IE2023 Programacion de Microcontroladores
 * PreLab5.c
 * Autor: Larsson Gonzalez
 * Proyecto:
 * Hardware: ATMega328p
 * Creado: 12/4/2024 08:17:01
 *************************************************************/ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PWMT1/PWMT1.h"

//************************************************************
// DECLARACION DE FUNCIONES
//************************************************************
void ADC_init(void);

//************************************************************
// DECLARACION DE VARIABLES
//************************************************************
uint8_t adcread;

//************************************************************
// SETUP
//************************************************************
int main(void)
{
	
	cli();
	PWMT1FastInitA(invertido, 1024);
	PWMT1FastInitB(noinvertido, 1024);
	ADC_init();
	
	int frecuency = 50; // Frecuencia 
	int dutyCycle;
	
	sei();
	
    //********************************************************
	// LOOP
	//********************************************************
    while (1) {
		
		// Actualizar el ciclo de trabajo para canal A y B
		updateDutyCycleA(frecuency, dutyCycleA);
		updateDutyCycleB(frecuency, dutyCycleB);
		
		_delay_ms(30);
		
		// Incrementa el ciclo de trabajo para canal A y B
		dutyCycleA += 10;
		if (dutyCycleA > 100){
			dutyCycleA = 0;	// Reiniciar ciclo de trabajo
		}
		
		dutyCycleB += 5;
		if (dutyCycleB > 100){
			dutyCycleB = 0;	// Reiniciar ciclo de trabajo
		}
		
    }
}

//************************************************************
// ISR
//************************************************************
ISR(ADC_vect){
	adcread = ADCH;
	ADCSRA |= (1<<ADIF);
}

//************************************************************
// FUNCIONES
//************************************************************

void ADC_init(){
	// Seleccion de Canal ADC (A)
	ADMUX = 0x07;
	
	// Utilizando AVCC = 5V internos
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	// Justificacion a la Izquierda
	ADMUX |= (1<<ADLAR);
	
	ADCSRA = 0;
	
	// Habilitando el ADC
	ADCSRA |= (1<<ADEN);
	
	//Habilitamos las interrupciones
	ADCSRA |= (1<<ADIE);
	
	// Habilitamos el Prescaler de 128
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	DIDR0 |= (1<<ADC0D);
}