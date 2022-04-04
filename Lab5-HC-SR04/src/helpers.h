#ifndef HELPERS
#define HELPERS

#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#define BUT2_PIO			PIOC
#define BUT2_PIO_ID			ID_PIOC
#define BUT2_IDX			31
#define BUT2_IDX_MASK		(1u << BUT2_IDX)

#define ECHO_PIO			PIOA
#define ECHO_PIO_ID			ID_PIOA
#define ECHO_IDX			24
#define ECHO_IDX_MASK		(1u << ECHO_IDX)

#define TRIG_PIO			PIOA
#define TRIG_PIO_ID			ID_PIOA
#define TRIG_IDX			2
#define TRIG_IDX_MASK		(1u << TRIG_IDX)

#define RTT_FREQ			32000.0
#define SOUND_V				340.0

void but2_callback(void);
void echo_callback(void);
void wave(void);
void clear_display(void);
void RTT_Handler(void);
void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource);
void io_init(void);

#endif