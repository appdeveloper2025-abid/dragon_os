/*
 * Dragon OS - Timer Driver (PIT)
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND 0x43
#define PIT_FREQUENCY 1193182

static volatile uint32_t timer_ticks = 0;

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void init_timer(uint32_t frequency) {
    uint32_t divisor = PIT_FREQUENCY / frequency;
    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xFF));
}

void timer_handler(void) {
    timer_ticks++;
}

uint32_t get_ticks(void) {
    return timer_ticks;
}

void sleep(uint32_t ms) {
    uint32_t target = timer_ticks + ms;
    while (timer_ticks < target) {
        __asm__ volatile ("hlt");
    }
}
