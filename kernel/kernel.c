/*
 * Dragon OS Kernel
 * Designed & Developed by ABID MEHMOOD
 * Version 1.0
 */

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

// Color definitions for Dragon OS theme
#define COLOR_BLACK 0x0
#define COLOR_BLUE 0x1
#define COLOR_CYAN 0x3
#define COLOR_RED 0x4
#define COLOR_MAGENTA 0x5
#define COLOR_WHITE 0xF

// External module declarations
extern void init_ui_engine(void);
extern void init_voice_module(void);
extern void init_security_module(void);
extern void render_holographic_ui(void);
extern void start_ai_assistant(void);

static uint16_t* vga_buffer = (uint16_t*)VGA_MEMORY;
static size_t terminal_row = 0;
static size_t terminal_column = 0;
static uint8_t terminal_color = 0x0F;

// VGA color helper
static inline uint8_t vga_color(uint8_t fg, uint8_t bg) {
    return fg | bg << 4;
}

// VGA entry helper
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

// String length
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

// Clear screen
void terminal_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    terminal_row = 0;
    terminal_column = 0;
}

// Set terminal color
void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

// Put character at position
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    vga_buffer[index] = vga_entry(c, color);
}

// Put character
void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) terminal_row = 0;
        return;
    }
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) terminal_row = 0;
    }
}

// Write string
void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

// Write string (null-terminated)
void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

// Display Dragon OS boot animation
void display_dragon_boot(void) {
    terminal_clear();
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    
    terminal_writestring("\n");
    terminal_writestring("        ====================================\n");
    terminal_setcolor(vga_color(COLOR_RED, COLOR_BLACK));
    terminal_writestring("                   DRAGON OS\n");
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    terminal_writestring("        ====================================\n\n");
    
    terminal_setcolor(vga_color(COLOR_BLUE, COLOR_BLACK));
    terminal_writestring("                      /\\_/\\\n");
    terminal_writestring("                     ( o.o )\n");
    terminal_writestring("                      > ^ <\n");
    terminal_writestring("                    /|     |\\\n");
    terminal_writestring("                   (_|     |_)\n\n");
    
    terminal_setcolor(vga_color(COLOR_MAGENTA, COLOR_BLACK));
    terminal_writestring("        Designed & Developed by ABID MEHMOOD\n\n");
    
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    terminal_writestring("        Version 1.0 - Live Operating System\n");
    terminal_writestring("        ====================================\n\n");
}

// Display system status
void display_system_status(void) {
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    terminal_writestring("\n  [*] Initializing Dragon OS Kernel...\n");
    terminal_setcolor(vga_color(COLOR_WHITE, COLOR_BLACK));
    terminal_writestring("  [OK] Kernel loaded successfully\n");
    
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    terminal_writestring("  [*] Loading Holographic UI Engine...\n");
    terminal_setcolor(vga_color(COLOR_WHITE, COLOR_BLACK));
    terminal_writestring("  [OK] UI Engine initialized\n");
    
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    terminal_writestring("  [*] Starting AI Voice Assistant...\n");
    terminal_setcolor(vga_color(COLOR_WHITE, COLOR_BLACK));
    terminal_writestring("  [OK] JARVIS AI Module active\n");
    
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    terminal_writestring("  [*] Loading Cybersecurity Suite...\n");
    terminal_setcolor(vga_color(COLOR_WHITE, COLOR_BLACK));
    terminal_writestring("  [OK] Security modules loaded\n\n");
    
    terminal_setcolor(vga_color(COLOR_RED, COLOR_BLACK));
    terminal_writestring("  >> Welcome back, System Ready.\n\n");
    
    terminal_setcolor(vga_color(COLOR_CYAN, COLOR_BLACK));
    terminal_writestring("  ====================================\n");
    terminal_writestring("  Dragon OS Desktop Environment\n");
    terminal_writestring("  ====================================\n\n");
}

// Main kernel entry point
void kernel_main(void) {
    // Display boot screen
    display_dragon_boot();
    
    // Small delay simulation
    for (volatile int i = 0; i < 50000000; i++);
    
    // Display system initialization
    display_system_status();
    
    // Initialize Dragon OS modules
    init_ui_engine();
    init_voice_module();
    init_security_module();
    
    // Start holographic UI
    render_holographic_ui();
    
    // Start AI assistant
    start_ai_assistant();
    
    terminal_setcolor(vga_color(COLOR_WHITE, COLOR_BLACK));
    terminal_writestring("  Type 'help' for available commands\n");
    terminal_writestring("  Dragon OS > ");
    
    // Kernel main loop
    while (1) {
        __asm__ volatile ("hlt");
    }
}
