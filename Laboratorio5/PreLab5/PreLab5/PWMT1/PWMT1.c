/*
 * PWMT1.c
 *
 * Created: 12/4/2024 09:04:57
 *  Author: polst
 */ 

#define F_CPU 16000000UL
#include "PWMT1.h"
#include <util/delay.h>



void PWMT1FastInitA(uint8_t inverted, uint16_t prescaler){
	//Pin Configuration OC1A
	DDRB |= (1<<DDB1);
	
	// Configurar el modo de salida PWM
	if (inverted){
		//Configuracion de modo Invertido
		TCCR1A |= (1<<COM1A1)|(1<<COM1A0); // PWM invertido
	} 
	else{
		//Configuracion de modo No Invertido
		TCCR1A |=  (1<<COM1A1);		// PWM no invertido
	}
	
	
	//Configuracion de Modo Fast PWM, TOP =	ICR1
	TCCR1A |=  (1<<WGM11);
	TCCR1B |=  (1<<WGM13)|(1<<WGM12); 
	
	if (prescaler == 1024){
		//Configuracion de Prescaler 1024
		TCCR1B &= ~(1<<CS11)|(1<<CS10);
		TCCR1B |=  (1<<CS12);
	}
	
}

void PWMT1FastInitB(uint8_t inverted, uint16_t prescaler){
	//Pin Configuration OC1B
	DDRB |= (1<<DDB2);
	
	if (inverted){
		//Configuracion de modo Invertido
		TCCR1A |= (1<<COM1B1)|(1<<COM1B0);	// PWM invertido
		
	} 
	else{
		//Configuracion de modo No Invertido
		TCCR1A |=  (1<<COM1B1); // PWM no invertido
	}
	
	
	//Configuracion de Modo Fast PWM, TOP = ICR1
	TCCR1A |=  (1<<WGM13);
	TCCR1A |=  (1<<WGM12);
	TCCR1A |=  (1<<WGM11);
	
	
	if (prescaler == 1024){
		//Configuracion de Prescaler 1024
		TCCR1B &= ~((1<<CS11)|(1<<CS10));
		TCCR1B |=  (1<<CS12);
	}

}

void updateDutyCycleA(int freq, int duty){
	uint16_t top = F_CPU/(1024UL * freq) - 1;
	ICR1 = top;
	OCR1A = (top*duty)/100;
}

void updateDutyCycleB(int freq, int duty){
	uint16_t top = F_CPU/(1024UL * freq) - 1;
	ICR1 = top;
	OCR1B = (top*duty)/100;
}