/*******************************************
 *  aula.c
 *  Created on: 06/10/2018 (eclipse, avr-gcc)
 *      Author: up201504257@fe.up.pt
 *
 *      Estado 1-> LUZ VERDE NORTE
 *      Estado 2-> LUZ AMARELA NORTE
 *      Estado 3-> LUZ VERMELHA NORTE
 *      Estado 4-> LUZ VERDE SUL
 *      Estado 5-> LUZ AMARELA SUL
 *      Estado 6-> LUZ VERMELHA SUL
 *
 *      Estado 10 -> EMERGENCIA DESATIVADA
 *      Estado 11 -> EMERGENCIA ATIVADA
 *******************************************/

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

uint8_t estado, estado_emergencia;
mili_timer T_Verde, T_Amarelo_vermelho;

/*Testa funcionamento de todos os LEDS */
void Testa_Leds();

/* Iniciação das variaveis e timers */
void hw_init(void);

/* Transições entre estados*/
void Estados();

/* Pisca o LED amarelo, posição irregular*/
void Erro();

/* Ativa as saidas (LEDS) de acordo com os estados*/
void Ativa_Saidas();


int main(void) {

	hw_init();

	while (1) {
		Estados();
		Ativa_Saidas();
	}

}

void Testa_Leds() {
	PORTB = (1 << GREEN_N);
	_delay_ms(200);
	PORTB = (1 << YELLOW_N);
	_delay_ms(200);
	PORTB = (1 << RED_N);
	_delay_ms(200);
	PORTB = (1 << GREEN_E);
	_delay_ms(200);
	PORTB = (1 << YELLOW_E);
	_delay_ms(200);
	PORTB = (1 << RED_E);
	_delay_ms(200);

	PORTB = (1 << GREEN_N) | (1 << YELLOW_N) | (1 << RED_N) | (1 << GREEN_E)
			| (1 << YELLOW_E) | (1 << RED_E);
	_delay_ms(1000);
	PORTB=0;
	_delay_ms(500); /*espera um pouco antes de começar o programa*/
}

void hw_init(void) {
	DDRB = (1 << RED_N) | (1 << YELLOW_N) | (1 << GREEN_N) | (1 << YELLOW_E)
			| (1 << GREEN_E) | (1 << RED_E);

	/*Estados iniciais*/
	estado = 1;
	estado_emergencia = 10;

	/*Tempos*/
	sei();
	init_mili_timers();

	/*Testa LEDS*/
	Testa_Leds();

	/* Inicio timer verde norte */
	start_timer(&T_Verde, 5000);


}

void Estados() {

	if (estado == 1 && get_timer(&T_Verde)) // tempo do verde N
			{
		estado = 2; /*Luz amarela N*/
		start_timer(&T_Amarelo_vermelho, 5000);

	} else if (estado == 2 && get_timer(&T_Amarelo_vermelho)) // tempo do amarelo N
			{
		estado = 3; /*Luz vermelha N*/
		start_timer(&T_Amarelo_vermelho, 5000);

	} else if (estado == 3 && get_timer(&T_Amarelo_vermelho)) // tempo do vermelho N
			{
		estado = 4; /*Luz verde E*/
		start_timer(&T_Verde, 5000);

	} else if (estado == 4 && get_timer(&T_Verde)) // tempo do verde E
			{
		estado = 5; /*Luz amarela E*/
		start_timer(&T_Amarelo_vermelho, 5000);

	} else if (estado == 5 && get_timer(&T_Amarelo_vermelho)) // tempo do amarelo E
			{
		estado = 6; /*Luz vermelha E*/
		start_timer(&T_Amarelo_vermelho, 5000);
	} else if (estado == 6 && get_timer(&T_Amarelo_vermelho)) // tempo do vermelho E
			{
		estado = 1; /* VERDE N*/
		start_timer(&T_Verde, 5000);

	}

	if (estado_emergencia == 10 && !(PIND & (1 << EMERGENCIA))) {
		estado_emergencia = 11;
	} else if (estado_emergencia == 11 && ((PIND & (1 << EMERGENCIA)))) {
		estado_emergencia = 10;
		if (estado >= 1 && estado <= 3) {
			estado = 4;
			start_timer(&T_Verde, 5000);

		} else if (estado >= 4 && estado <= 6) {
			estado = 1;
			start_timer(&T_Verde, 5000);
		}

	}
}

void Erro(){
	while(1) {
		PORTB = (1 << YELLOW_N) | (1 << YELLOW_E);
		_delay_ms(1000);
		PORTB=0;
		_delay_ms(1000);
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
		/*PISCAR AMARELO A CADA SEGUNDO
		 * POSIÇÃO IRREGULAR ATINGIDA*/
		Erro();
		break;
	}

	/* ATIVA VERMELHO NORTE, ATIVA VERMELHO SUL*/
	if (estado_emergencia == 11) {

		PORTB = (1 << RED_N) | ((1 << RED_E));
		_delay_ms(2000);		// Tempo de espera para depois recomeçar

	} else if (estado_emergencia != 10)
		Erro();// Posição irregular atingida | APENAS PODE SER ** 10 OU 11 **

}


