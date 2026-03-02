/*
 * Dragon OS - Mouse Driver (PS/2)
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define MOUSE_DATA 0x60
#define MOUSE_STATUS 0x64
#define MOUSE_CMD 0x64

static int8_t mouse_x = 0;
static int8_t mouse_y = 0;
static uint8_t mouse_buttons = 0;

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void mouse_wait(uint8_t type) {
    uint32_t timeout = 100000;
    if (type == 0) {
        while (timeout--) {
            if ((inb(MOUSE_STATUS) & 1) == 1) return;
        }
    } else {
        while (timeout--) {
            if ((inb(MOUSE_STATUS) & 2) == 0) return;
        }
    }
}

void mouse_write(uint8_t data) {
    mouse_wait(1);
    outb(MOUSE_CMD, 0xD4);
    mouse_wait(1);
    outb(MOUSE_DATA, data);
}

uint8_t mouse_read(void) {
    mouse_wait(0);
    return inb(MOUSE_DATA);
}

void init_mouse(void) {
    mouse_wait(1);
    outb(MOUSE_CMD, 0xA8);
    mouse_wait(1);
    outb(MOUSE_CMD, 0x20);
    uint8_t status = mouse_read() | 2;
    mouse_wait(1);
    outb(MOUSE_CMD, 0x60);
    mouse_wait(1);
    outb(MOUSE_DATA, status);
    mouse_write(0xF6);
    mouse_read();
    mouse_write(0xF4);
    mouse_read();
}

void mouse_handler(void) {
    static uint8_t cycle = 0;
    static uint8_t packet[3];
    
    packet[cycle++] = inb(MOUSE_DATA);
    
    if (cycle == 3) {
        cycle = 0;
        mouse_buttons = packet[0] & 0x07;
        mouse_x = packet[1];
        mouse_y = packet[2];
    }
}

void get_mouse_position(int8_t* x, int8_t* y) {
    *x = mouse_x;
    *y = mouse_y;
}

uint8_t get_mouse_buttons(void) {
    return mouse_buttons;
}
