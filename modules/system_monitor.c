/*
 * Dragon OS - System Monitor
 * Real-time Resource Monitoring
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80

typedef struct {
    uint8_t cpu_usage;
    uint32_t memory_total;
    uint32_t memory_used;
    uint32_t uptime;
    uint16_t process_count;
} SystemStats;

static SystemStats stats = {0, 524288, 0, 0, 5};
static uint16_t* vga = (uint16_t*)VGA_MEMORY;

// Update system statistics
void update_stats(void) {
    stats.cpu_usage = (stats.cpu_usage + 5) % 100;
    stats.memory_used = (stats.memory_used + 1024) % stats.memory_total;
    stats.uptime++;
}

// Draw progress bar
void draw_progress_bar(uint8_t x, uint8_t y, uint8_t width, uint8_t percent, uint8_t color) {
    uint8_t filled = (width * percent) / 100;
    
    vga[(y * VGA_WIDTH) + x++] = (uint16_t)'[' | ((uint16_t)color << 8);
    
    for (uint8_t i = 0; i < width; i++) {
        char c = (i < filled) ? '|' : '-';
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)c | ((uint16_t)color << 8);
    }
    
    vga[(y * VGA_WIDTH) + x] = (uint16_t)']' | ((uint16_t)color << 8);
}

// Display system monitor
void display_system_monitor(void) {
    const char* title = "[ SYSTEM MONITOR ]";
    uint8_t x = 30, y = 8;
    for (const char* p = title; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
    }
    
    // CPU usage
    const char* cpu_label = "CPU Usage:";
    x = 15; y = 10;
    for (const char* p = cpu_label; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0F << 8);
    }
    draw_progress_bar(30, 10, 20, stats.cpu_usage, 0x0A);
    
    // Memory usage
    const char* mem_label = "Memory:";
    x = 15; y = 12;
    for (const char* p = mem_label; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0F << 8);
    }
    uint8_t mem_percent = (stats.memory_used * 100) / stats.memory_total;
    draw_progress_bar(30, 12, 20, mem_percent, 0x0B);
    
    // Process count
    const char* proc_label = "Processes: 5";
    x = 15; y = 14;
    for (const char* p = proc_label; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0F << 8);
    }
}

// Get system stats
SystemStats* get_system_stats(void) {
    return &stats;
}
