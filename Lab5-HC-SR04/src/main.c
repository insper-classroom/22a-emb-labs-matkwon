#include <asf.h>

#include "helpers.h"

volatile char flag_but2 = 0;
volatile char flag_echo = 0;
volatile long rtt_timer = 0;
volatile float dist = 0;

void but2_callback(void) {
	flag_but2 = 1;
}

void echo_callback(void) {
	if (pio_get(ECHO_PIO, PIO_INPUT, ECHO_IDX_MASK)) {
		RTT_init(RTT_FREQ, 0, 0);
	} else {
		rtt_timer = rtt_read_timer_value(RTT);
		flag_echo = 1;
	}
}

int main(void) {
    board_init();
    sysclk_init();
    delay_init();
    WDT->WDT_MR = WDT_MR_WDDIS;

    io_init();
	int scan = 0;

    // Init OLED
    gfx_mono_ssd1306_init();
    char str[8];
    sprintf(str, "%d cm   ", dist);
    gfx_mono_draw_string(str, 0, 0, &sysfont);

    /* Insert application code here, after the board has been initialized. */
    while (1) {
        if (flag_but2) {
            wave();
            flag_but2 = 0;
        }
        if (flag_echo) {
            dist = rtt_timer * SOUND_V * 100 / (RTT_FREQ*2);
			clear_display();
			if (dist > 2.000 && dist < 400.000) {
				sprintf(str, "%0.1f cm", dist);
				gfx_mono_draw_string(str, 0, 0, &sysfont);
				if (scan == 0) {
					for (int i = 0; i<128; i++){
						gfx_mono_draw_rect(0, 16, i, 16, GFX_PIXEL_CLR);
					}
				}
				gfx_mono_draw_rect(scan*8, 16*(2 - dist/400), 8, 16*(dist/400), GFX_PIXEL_SET);
				scan = (scan+1)%16;
			} else {
				gfx_mono_draw_string("SCAN ERROR", 0, 0, &sysfont);
			}
            flag_echo = 0;
        }
        pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
    }
}
