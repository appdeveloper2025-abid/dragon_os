/*
 * Dragon OS - File Manager
 * Holographic File Browser
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define MAX_FILES 50

typedef struct {
    char name[32];
    uint32_t size;
    uint8_t type; // 0=file, 1=directory
} FileEntry;

static uint16_t* vga = (uint16_t*)VGA_MEMORY;
static FileEntry files[MAX_FILES];
static int file_count = 0;

// Initialize file system
void init_filesystem(void) {
    // Add sample files
    files[0] = (FileEntry){"system", 0, 1};
    files[1] = (FileEntry){"home", 0, 1};
    files[2] = (FileEntry){"boot", 0, 1};
    files[3] = (FileEntry){"dragon_os.bin", 524288, 0};
    files[4] = (FileEntry){"config.sys", 1024, 0};
    file_count = 5;
}

// Display file manager UI
void display_file_manager(void) {
    // Header
    const char* header = "[ DRAGON OS FILE MANAGER ]";
    uint8_t x = 25, y = 5;
    for (const char* p = header; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
    }
    
    // File list
    y = 7;
    for (int i = 0; i < file_count; i++) {
        x = 10;
        char icon = files[i].type ? '/' : '-';
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)icon | ((uint16_t)0x0E << 8);
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)' ' | ((uint16_t)0x0F << 8);
        
        for (const char* p = files[i].name; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0F << 8);
        }
        y++;
    }
}

// Open file
void open_file(const char* filename) {
    // File opening logic
}

// Create directory
void create_directory(const char* dirname) {
    if (file_count < MAX_FILES) {
        for (int i = 0; i < 32 && dirname[i]; i++) {
            files[file_count].name[i] = dirname[i];
        }
        files[file_count].type = 1;
        files[file_count].size = 0;
        file_count++;
    }
}
