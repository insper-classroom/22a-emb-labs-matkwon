/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED1_PIO          PIOA
#define LED1_PIO_ID       ID_PIOA
#define LED1_PIO_IDX      0
#define LED1_PIO_IDX_MASK (1 << LED1_PIO_IDX)

#define LED2_PIO          PIOC
#define LED2_PIO_ID       ID_PIOC
#define LED2_PIO_IDX      30
#define LED2_PIO_IDX_MASK (1 << LED2_PIO_IDX)

#define LED3_PIO          PIOB
#define LED3_PIO_ID       ID_PIOB
#define LED3_PIO_IDX      2
#define LED3_PIO_IDX_MASK (1 << LED3_PIO_IDX)

#define BUT1_PIO		  PIOD
#define BUT1_PIO_ID		  ID_PIOD
#define BUT1_PIO_IDX	  28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

#define BUT2_PIO		  PIOC
#define BUT2_PIO_ID		  ID_PIOC
#define BUT2_PIO_IDX	  31
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX)

#define BUT3_PIO		  PIOA
#define BUT3_PIO_ID		  ID_PIOA
#define BUT3_PIO_IDX	  19
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX)


/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
// Função de inicialização do uC
void init(void) {
	
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);
	
	//Inicializa PC8 como saída
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);
	
	pio_set_input(LED1_PIO, BUT1_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(LED2_PIO, BUT2_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(LED3_PIO, BUT3_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(LED1_PIO, BUT1_PIO_IDX_MASK, PIO_PULLUP);
	pio_pull_up(LED2_PIO, BUT2_PIO_IDX_MASK, PIO_PULLUP);
	pio_pull_up(LED3_PIO, BUT3_PIO_IDX_MASK, PIO_PULLUP);

}


/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void) {
	// inicializa sistema e IOs
	init();

	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1)
	{
		delay_ms(10);                        // Delay por software de 10 ms
		if(!pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK)) {
			for (int i = 0; i < 5; i++) {
				pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
				delay_ms(200);
				pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
				delay_ms(200);
			}
		} else {
			pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		if(!pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK)) {
			for (int i = 0; i < 5; i++) {
				pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
				delay_ms(200);
				pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
				delay_ms(200);
			}
		} else {
			pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		}
		if(!pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK)) {
			for (int i = 0; i < 5; i++) {
				pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
				delay_ms(200);
				pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
				delay_ms(200);
			}
		} else {
			pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
		}
	}
	return 0;
}

