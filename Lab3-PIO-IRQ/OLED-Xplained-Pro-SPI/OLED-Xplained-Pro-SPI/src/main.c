#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

/*  Default pin configuration (no attribute). */
#define _PIO_DEFAULT             (0u << 0)
/*  The internal pin pull-up is active. */
#define _PIO_PULLUP              (1u << 0)
/*  The internal glitch filter is active. */
#define _PIO_DEGLITCH            (1u << 1)
/*  The internal debouncing filter is active. */
#define _PIO_DEBOUNCE            (1u << 3)

#define LED_PIO           PIOC
#define LED_PIO_ID        ID_PIOC
#define LED_IDX			  30
#define LED_IDX_MASK	  (1 << LED_IDX)

#define BUT1_PIO		  PIOD
#define BUT1_PIO_ID		  ID_PIOD
#define BUT1_IDX		  28
#define BUT1_IDX_MASK	  (1u << BUT1_IDX)

#define BUT2_PIO		  PIOC
#define BUT2_PIO_ID		  ID_PIOC
#define BUT2_IDX		  31
#define BUT2_IDX_MASK	  (1u << BUT2_IDX)

#define BUT3_PIO		  PIOA
#define BUT3_PIO_ID		  ID_PIOA
#define BUT3_IDX		  19
#define BUT3_IDX_MASK	  (1u << BUT3_IDX)

volatile char but1_flag;
volatile char but2_flag;
volatile char but3_flag;

void but1_callback(void);
void but2_callback(void);
void but3_callback(void);
void pisca_led(int duration, int f);
void incremento(char str[], int *pc);
void decremento(char str[], int *pc);
void io_init(void);

void but1_callback(void)
{
	if (pio_get(BUT1_PIO, PIO_INPUT, BUT1_IDX_MASK)) {
		but1_flag = 0;
	} else {
		but1_flag = 1;
	}
}

void but2_callback(void)
{
	but2_flag = 1;
}

void but3_callback(void)
{
	but3_flag = 1;
}

void pisca_led(int duration, int f){
	if (f>0) {
		long t = 500/f;
		int n = duration*f;
		for (int i = 0; i < n; i++){
			for (int j = 128*i/n; j < 128*(i+1)/n; j++) {
				gfx_mono_draw_rect(0, 25, j, 7, GFX_PIXEL_SET);
			}
			pio_clear(LED_PIO, LED_IDX_MASK);
			delay_ms(t);
			pio_set(LED_PIO, LED_IDX_MASK);
			delay_ms(t);
		}
		for (int i = 0; i<128; i++){
			gfx_mono_draw_rect(0, 25, i, 7, GFX_PIXEL_CLR);
		}
	}
}

void incremento(char str[], int *pc) {
	*pc += 1;
	sprintf(str, "f: %d Hz  ", *pc);
}

void decremento(char str[], int *pc) {
	if (*pc != 0)
		*pc -= 1;
	sprintf(str, "f: %d Hz  ", *pc);
}

void io_init(void)
{
	
	but1_flag = 0;
	but2_flag = 0;
	but3_flag = 0;

	// Configura led
	pmc_enable_periph_clk(LED_PIO_ID);
	pio_configure(LED_PIO, PIO_OUTPUT_0, LED_IDX_MASK, PIO_DEFAULT);

	// Inicializa clock do periférico PIO responsavel pelo botao
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);

	// Configura PIO para lidar com o pino do botão como entrada
	// com pull-up
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT1_PIO, BUT1_IDX_MASK, 60);
	
	pio_configure(BUT2_PIO, PIO_INPUT, BUT2_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT2_PIO, BUT2_IDX_MASK, 60);
	
	pio_configure(BUT3_PIO, PIO_INPUT, BUT3_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT3_PIO, BUT3_IDX_MASK, 60);

	// Configura interrupção no pino referente ao botao e associa
	// função de callback caso uma interrupção for gerada
	// a função de callback é a: but1_callback()
	pio_handler_set(BUT1_PIO,
					BUT1_PIO_ID,
					BUT1_IDX_MASK,
					PIO_IT_EDGE,
					but1_callback);
	
	pio_handler_set(BUT2_PIO,
					BUT2_PIO_ID,
					BUT2_IDX_MASK,
					PIO_IT_RISE_EDGE,
					but2_callback);
					
	pio_handler_set(BUT3_PIO,
					BUT3_PIO_ID,
					BUT3_IDX_MASK,
					PIO_IT_RISE_EDGE,
					but3_callback);

	// Ativa interrupção e limpa primeira IRQ gerada na ativacao
	pio_enable_interrupt(BUT1_PIO, BUT1_IDX_MASK);
	pio_get_interrupt_status(BUT1_PIO);
	
	pio_enable_interrupt(BUT2_PIO, BUT2_IDX_MASK);
	pio_get_interrupt_status(BUT2_PIO);
	
	pio_enable_interrupt(BUT3_PIO, BUT3_IDX_MASK);
	pio_get_interrupt_status(BUT3_PIO);
	
	// Configura NVIC para receber interrupcoes do PIO do botao
	// com prioridade 4 (quanto mais próximo de 0 maior)
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, 4); // Prioridade 4
	
	pio_set(LED_PIO, LED_IDX_MASK);
}

int main (void)
{
	int freq = 1;
	char str[128];
	sprintf(str, "f: %d Hz  ", freq);
	
	board_init();
	sysclk_init();
	io_init();
	delay_init();

	// Init OLED
	gfx_mono_ssd1306_init();
  
	// Escreve na tela um circulo e um texto
	// gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_string(str, 0, 0, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {
		if (but1_flag) {
			delay_ms(300);
			if (but1_flag) {
				decremento(str, &freq);
			} else {
				incremento(str, &freq);
			}
			gfx_mono_draw_string(str, 0, 0, &sysfont);
			but1_flag = 0;
		}
		if (but2_flag) {
			pisca_led(4, freq);
			but2_flag = 0;
		}
		if (but3_flag) {
			decremento(str, &freq);
			gfx_mono_draw_string(str, 0, 0, &sysfont);
			but3_flag = 0;
		}
		pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
	}
}
