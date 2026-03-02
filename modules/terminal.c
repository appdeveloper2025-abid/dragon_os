/*
 * Dragon OS - Terminal Emulator
 * Futuristic Command Interface
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint16_t* vga = (uint16_t*)VGA_MEMORY;
static char command_buffer[256];
static uint8_t cmd_pos = 0;

// Terminal commands
typedef struct {
    const char* cmd;
    const char* description;
    void (*handler)(void);
} Command;

void cmd_help(void);
void cmd_clear(void);
void cmd_about(void);
void cmd_status(void);
void cmd_scan(void);
void cmd_exit(void);

static Command commands[] = {
    {"help", "Show available commands", cmd_help},
    {"clear", "Clear terminal screen", cmd_clear},
    {"about", "About Dragon OS", cmd_about},
    {"status", "System status", cmd_status},
    {"scan", "Security scan", cmd_scan},
    {"exit", "Exit terminal", cmd_exit},
    {0, 0, 0}
};

// Command handlers
void cmd_help(void) {
    const char* help_text[] = {
        "Dragon OS Terminal Commands:",
        "  help    - Show this help",
        "  clear   - Clear screen",
        "  about   - About Dragon OS",
        "  status  - System status",
        "  scan    - Run security scan",
        "  exit    - Exit terminal"
    };
    
    uint8_t y = 10;
    for (int i = 0; i < 7; i++) {
        uint8_t x = 5;
        for (const char* p = help_text[i]; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
        }
        y++;
    }
}

void cmd_clear(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = (uint16_t)' ' | ((uint16_t)0x00 << 8);
    }
}

void cmd_about(void) {
    const char* about[] = {
        "Dragon OS Version 1.0",
        "Designed & Developed by ABID MEHMOOD",
        "",
        "A futuristic operating system featuring:",
        "- Holographic UI",
        "- AI Voice Assistant",
        "- Cybersecurity Suite",
        "- Live Boot Mode"
    };
    
    uint8_t y = 10;
    for (int i = 0; i < 8; i++) {
        uint8_t x = 5;
        for (const char* p = about[i]; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
        }
        y++;
    }
}

void cmd_status(void) {
    const char* status = "System: OPERATIONAL | CPU: 80% | Memory: 60% | Security: ACTIVE";
    uint8_t x = 5, y = 12;
    for (const char* p = status; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0A << 8);
    }
}

void cmd_scan(void) {
    const char* scan = "Running security scan... No threats detected.";
    uint8_t x = 5, y = 12;
    for (const char* p = scan; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0A << 8);
    }
}

void cmd_exit(void) {
    const char* exit_msg = "Exiting terminal...";
    uint8_t x = 5, y = 12;
    for (const char* p = exit_msg; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0E << 8);
    }
}

// Process command
void process_command(const char* cmd) {
    for (int i = 0; commands[i].cmd; i++) {
        const char* c1 = cmd;
        const char* c2 = commands[i].cmd;
        int match = 1;
        
        while (*c1 && *c2) {
            if (*c1 != *c2) {
                match = 0;
                break;
            }
            c1++; c2++;
        }
        
        if (match && *c2 == '\0') {
            if (commands[i].handler) {
                commands[i].handler();
            }
            return;
        }
    }
    
    const char* unknown = "Unknown command. Type 'help' for available commands.";
    uint8_t x = 5, y = 12;
    for (const char* p = unknown; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0C << 8);
    }
}

// Display terminal prompt
void display_prompt(void) {
    const char* prompt = "dragon@os:~$ ";
    uint8_t x = 5, y = 20;
    for (const char* p = prompt; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
    }
}

// Initialize terminal
void init_terminal(void) {
    cmd_clear();
    const char* welcome = "Dragon OS Terminal - Type 'help' for commands";
    uint8_t x = 15, y = 5;
    for (const char* p = welcome; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
    }
    display_prompt();
}
