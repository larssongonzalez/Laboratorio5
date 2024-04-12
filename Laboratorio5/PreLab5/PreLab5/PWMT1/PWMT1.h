/*
 * PWMT1.h
 *
 * Created: 12/4/2024 08:46:40
 *  Author: polst
 */ 


#ifndef PWMT1_H_
#define PWMT1_H_

#include <stdint.h>
#include <avr/io.h>
#define invertido 1
#define noinvertido 0
/*Funcion de Configuracion de PWMT1 en modo FAST Canal A*/
void PWMT1FastInitA(uint8_t inverted, uint16_t prescaler);

/*Funcion de Configuracion de PWMT1 en modo FAST Canal B*/
void PWMT1FastInitB(uint8_t inverted, uint16_t prescaler);

/*Establezco valor de frecuencia y ciclo de trabajo*/
void updateDutyCycleA(int freq, int duty);

/*Establezco valor de frecuencia y ciclo de trabajo*/
void updateDutyCycleB(int freq, int duty);

#endif /* PWMT1_H_ */