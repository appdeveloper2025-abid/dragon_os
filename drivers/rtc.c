/*
 * Dragon OS - RTC (Real-Time Clock) Driver
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define RTC_ADDRESS 0x70
#define RTC_DATA 0x71

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t rtc_read(uint8_t reg) {
    outb(RTC_ADDRESS, reg);
    return inb(RTC_DATA);
}

void rtc_write(uint8_t reg, uint8_t value) {
    outb(RTC_ADDRESS, reg);
    outb(RTC_DATA, value);
}

uint8_t bcd_to_binary(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void init_rtc(void) {
    outb(RTC_ADDRESS, 0x8B);
    uint8_t prev = inb(RTC_DATA);
    outb(RTC_ADDRESS, 0x8B);
    outb(RTC_DATA, prev | 0x40);
}

void get_time(uint8_t* hour, uint8_t* minute, uint8_t* second) {
    *second = bcd_to_binary(rtc_read(0x00));
    *minute = bcd_to_binary(rtc_read(0x02));
    *hour = bcd_to_binary(rtc_read(0x04));
}

void get_date(uint8_t* day, uint8_t* month, uint16_t* year) {
    *day = bcd_to_binary(rtc_read(0x07));
    *month = bcd_to_binary(rtc_read(0x08));
    *year = bcd_to_binary(rtc_read(0x09)) + 2000;
}
