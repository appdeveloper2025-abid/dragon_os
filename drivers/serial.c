/*
 * Dragon OS - Serial Port Driver
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define COM1 0x3F8

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void init_serial(void) {
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

int serial_received(void) {
    return inb(COM1 + 5) & 1;
}

char serial_read(void) {
    while (!serial_received());
    return inb(COM1);
}

int serial_transmit_empty(void) {
    return inb(COM1 + 5) & 0x20;
}

void serial_write(char c) {
    while (!serial_transmit_empty());
    outb(COM1, c);
}

void serial_writestring(const char* str) {
    while (*str) {
        serial_write(*str++);
    }
}
