///*******************************************
// *  blink.c
// *  A blinking LED demo written in plain C
// *  using the Arduino platform LED on PB5
// *  Created on: 06/10/2018 (eclipse, avr-gcc)
// *      Author: up201504257@fe.up.pt
// *******************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer_tools.h"

#define RED_E PB5
#define YELLOW_E PB4
#define GREEN_E PB3

#define RED_N PB2
#define YELLOW_N PB1
#define GREEN_N PB0

#define EMERGENCIA PD7

unsigned char estado, estado_emergencia;
mili_timer T_Verde, T_Amarelo_vermelho;

void hw_init(void) {
	DDRB = (1 << RED_N) | (1 << YELLOW_N) | (1 << GREEN_N) | (1 << YELLOW_E)
			| (1 << GREEN_E) | (1 << RED_E);

	estado = 1;
	estado_emergencia = 10;

	sei();
	init_mili_timers();
	start_timer(&T_Verde, 5000);

}

void Estados() {

	/*Luz amarela N*/
	if (estado == 1 && get_timer(&T_Verde)) // tempo do verde N
			{
		estado = 2;
		start_timer(&T_Amarelo_vermelho, 5000);

	}
	/*Luz vermelha N*/
	else if (estado == 2 && get_timer(&T_Amarelo_vermelho)) // tempo do amarelo N
			{
		estado = 3;
		start_timer(&T_Amarelo_vermelho, 5000);

	}
	/*Luz verde E*/
	else if (estado == 3 && get_timer(&T_Amarelo_vermelho)) // tempo do vermelho N
			{
		estado = 4;
		start_timer(&T_Verde, 5000);

	}
	/*Luz amarela E*/
	else if (estado == 4 && get_timer(&T_Verde)) // tempo do verde E
			{
		estado = 5;
		start_timer(&T_Amarelo_vermelho, 5000);

	}
	/*Luz vermelha E*/
	else if (estado == 5 && get_timer(&T_Amarelo_vermelho)) // tempo do amarelo E
			{
		estado = 6;
		start_timer(&T_Amarelo_vermelho, 5000);
	}
	/* VOLTA PARA ESTADO INICIAL*/
	else if (estado == 6 && get_timer(&T_Amarelo_vermelho)) // tempo do vermelho E
			{
		estado = 1;
	}

	if (estado_emergencia == 10 && !(PIND & (1 << EMERGENCIA))) {
		estado_emergencia = 11;
	} else if (estado_emergencia == 11 && ((PIND & (1 << EMERGENCIA)))) {
		estado_emergencia = 10;
	}
}

void Ativa_Saidas() {
	switch (estado) {

	case 1:
		/*ATIVA VERDE NORTE,
		 * ATIVA VERMELHO SUL*/
		PORTB = ((1 << GREEN_N) | (1 << RED_E));
		break;

	case 2:
		/*ATIVA AMARELO NORTE,
		 * DEIXA ATIVO VERMELHO SUL,
		 * DESATIVA VERDE NORTE*/
		PORTB = (PORTB & (~(1 << GREEN_N))) | ((1 << YELLOW_N));
		break;

	case 3:
		/*ATIVA VERMELHO NORTE,
		 * DEIXA ATIVO VERMELHO SUL,
		 * DESATIVA AMARELO NORTE*/
		PORTB = (PORTB & (~(1 << YELLOW_N))) | ((1 << RED_N));
		break;

	case 4:
		/*DEIXA ATIVO VERMELHO NORTE,
		 * ATIVA VERDE SUL,
		 * DESATIVA VERMELHO SUL*/
		PORTB = (PORTB & (~(1 << RED_E))) | ((1 << GREEN_E));
		break;

	case 5:
		/*ATIVA AMARELO SUL,
		 * DEIXA ATIVO VERMELHO NORTE,
		 * DESATIVA VERDE SUL*/
		PORTB = (PORTB & (~(1 << GREEN_E))) | ((1 << YELLOW_E));
		break;

	case 6:
		/*ATIVA VERMELHO SUL,
		 *DEIXA ATIVO VERMELHO NORTE,
		 *DEIXA DESATIVA AMARELO SUL*/
		PORTB = (PORTB & (~(1 << YELLOW_E))) | ((1 << RED_E));
		break;

	default:
		/*PISCAR AMARELO A CADA SEGUNDO*/
		for (;;) {
			PORTB = (1 << YELLOW_N) | (1 << YELLOW_E);
			_delay_ms(1000);
		}
		break;
	}
	if (estado_emergencia == 11) {

		PORTB = (1 << RED_N) | ((1 << RED_E));
		_delay_ms(2000);
		if (estado >= 1 && estado <= 3)
			{
			estado = 4;
			start_timer(&T_Verde, 5000);

			}
		else if (estado >= 4 && estado <= 5)
			{
			estado = 1;
			start_timer(&T_Amarelo_vermelho, 5000);
			}
		estado_emergencia=10;
	}
}
int main(void) {
	hw_init();

	while (1) {
		Estados();
		Ativa_Saidas();
	}

}

