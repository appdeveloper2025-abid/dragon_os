/*
 * Dragon OS - Driver Headers
 * Designed & Developed by ABID MEHMOOD
 */

#ifndef DRIVERS_H
#define DRIVERS_H

#include <stdint.h>

// Keyboard Driver
void init_keyboard(void);
char keyboard_read(void);
int keyboard_available(void);

// VGA Driver
void init_vga(void);
void vga_putchar(char c, uint8_t color, uint8_t x, uint8_t y);
void vga_clear(uint8_t color);
void vga_scroll(void);
void vga_update_cursor(uint8_t x, uint8_t y);

// Timer Driver
void init_timer(uint32_t frequency);
void timer_handler(void);
uint32_t get_ticks(void);
void sleep(uint32_t ms);

// Disk Driver
void init_disk(void);
void disk_read_sector(uint32_t lba, uint8_t* buffer);
void disk_write_sector(uint32_t lba, uint8_t* buffer);

// Serial Driver
void init_serial(void);
int serial_received(void);
char serial_read(void);
int serial_transmit_empty(void);
void serial_write(char c);
void serial_writestring(const char* str);

// PCI Driver
uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void pci_write(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value);
uint16_t pci_get_vendor(uint8_t bus, uint8_t slot);
uint16_t pci_get_device(uint8_t bus, uint8_t slot);
void init_pci(void);

// Mouse Driver
void mouse_wait(uint8_t type);
void mouse_write(uint8_t data);
uint8_t mouse_read(void);
void init_mouse(void);
void mouse_handler(void);
void get_mouse_position(int8_t* x, int8_t* y);
uint8_t get_mouse_buttons(void);

// RTC Driver
uint8_t rtc_read(uint8_t reg);
void rtc_write(uint8_t reg, uint8_t value);
uint8_t bcd_to_binary(uint8_t bcd);
void init_rtc(void);
void get_time(uint8_t* hour, uint8_t* minute, uint8_t* second);
void get_date(uint8_t* day, uint8_t* month, uint16_t* year);

#endif
