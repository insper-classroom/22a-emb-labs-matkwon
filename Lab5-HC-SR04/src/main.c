#include <asf.h>

#include "gfx_mono_text.h"
#include "gfx_mono_ug_2832hsweg04.h"
#include "sysfont.h"

#define BUT2_PIO PIOC
#define BUT2_PIO_ID ID_PIOC
#define BUT2_IDX 31
#define BUT2_IDX_MASK (1u << BUT2_IDX)

#define ECHO_PIO PIOA
#define ECHO_PIO_ID ID_PIOA
#define ECHO_IDX 24
#define ECHO_IDX_MASK (1u << ECHO_PIO_IDX)

#define TRIG_PIO PIOA
#define TRIG_PIO_ID ID_PIOA
#define TRIG_IDX 2
#define TRIG_IDX_MASK (1u << TRIG_PIO_IDX)

volatile char flag_but2 = 0;
volatile char flag_echo = 0;
volatile long counter = 0;
float sound_v = 340;

void but2_callback(void);
void echo_callback(void);
void RTT_Handler(void);
static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource);
void io_init(void);

void but2_callback(void) {
    flag_but2 = 1;
}

void echo_callback(void) {
    flag_echo = 1;
}

void RTT_Handler(void) {
    uint32_t ul_status;

    /* Get RTT status - ACK */
    ul_status = rtt_get_status(RTT);

    /* IRQ due to Alarm */
    if ((ul_status & RTT_SR_ALMS) == RTT_SR_ALMS) {
        RTT->RTT_MR = RTT->RTT_MR | 1 << 18;
    }

    /* IRQ due to Time has changed */
    if ((ul_status & RTT_SR_RTTINC) == RTT_SR_RTTINC) {
    }
}

static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource) {

    uint16_t pllPreScale = (int)(((float)32768) / freqPrescale);

    rtt_sel_source(RTT, false);
    rtt_init(RTT, pllPreScale);

    if (rttIRQSource & RTT_MR_ALMIEN) {
        uint32_t ul_previous_time;
        ul_previous_time = rtt_read_timer_value(RTT);
        while (ul_previous_time == rtt_read_timer_value(RTT))
            ;
        rtt_write_alarm_time(RTT, IrqNPulses + ul_previous_time);
    }

    /* config NVIC */
    NVIC_DisableIRQ(RTT_IRQn);
    NVIC_ClearPendingIRQ(RTT_IRQn);
    NVIC_SetPriority(RTT_IRQn, 4);
    NVIC_EnableIRQ(RTT_IRQn);

    /* Enable RTT interrupt */
    if (rttIRQSource & (RTT_MR_RTTINCIEN | RTT_MR_ALMIEN))
        rtt_enable_interrupt(RTT, rttIRQSource);
    else
        rtt_disable_interrupt(RTT, RTT_MR_RTTINCIEN | RTT_MR_ALMIEN);
}

void io_init(void) {

    pmc_enable_periph_clk(BUT2_PIO_ID);
    pio_configure(BUT2_PIO, PIO_INPUT, BUT2_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
    pio_set_debounce_filter(BUT2_PIO, BUT2_IDX_MASK, 60);
    pio_handler_set(BUT2_PIO,
                    BUT2_PIO_ID,
                    BUT2_IDX_MASK,
                    PIO_IT_FALL_EDGE,
                    but2_callback);

    pmc_enable_periph_clk(TRIG_PIO_ID);
    pio_set_output(TRIG_PIO, TRIG_IDX_MASK, 1, 0, 0);

    pmc_enable_periph_clk(ECHO_PIO_ID);
    pio_configure(ECHO_PIO, PIO_INPUT, ECHO_IDX_MASK, PIO_DEBOUNCE);
    pio_set_debounce_filter(ECHO_PIO, ECHO_IDX_MASK, 60);
    pio_handler_set(ECHO_PIO,
                    ECHO_PIO_ID,
                    ECHO_IDX_MASK,
                    PIO_IT_FALL_EDGE,
                    echo_callback);

    pio_enable_interrupt(BUT2_PIO, BUT2_IDX_MASK);
    pio_get_interrupt_status(BUT2_PIO);
    NVIC_EnableIRQ(BUT2_PIO_ID);
    NVIC_SetPriority(BUT2_PIO_ID, 4);
}

int main(void) {
    board_init();
    sysclk_init();
    delay_init();
    WDT->WDT_MR = WDT_MR_WDDIS;

    io_init();

    int dist = 0;

    // Init OLED
    gfx_mono_ssd1306_init();
    char str[8];
    sprintf(str, "%d", dist);
    gfx_mono_draw_string(str, 0, 0, &sysfont);

    /* Insert application code here, after the board has been initialized. */
    while (1) {
        if (flag_but2) {
            pio_set(TRIG_PIO, TRIG_IDX_MASK);
            RTT_init(4, 16, RTT_MR_ALMIEN);
            delay_us(10);
            pio_clear(TRIG_PIO, TRIG_IDX_MASK);
            flag_but2 = 0;
        }
        if (flag_echo) {
            counter = rtt_read_timer_value(&RTT);
            dist = counter * sound_v / 2;
            sprintf(str, "%d m  ", dist);
            gfx_mono_draw_string(str, 0, 0, &sysfont);
            flag_echo = 0;
        }
        pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
    }
}
