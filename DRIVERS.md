# 🐉 DRAGON OS - Hardware Drivers Documentation

**Designed & Developed by ABID MEHMOOD**

---

## 📦 Available Drivers

Dragon OS includes 8 essential hardware drivers for complete system functionality:

---

## 1. ⌨️ Keyboard Driver (keyboard.c)

### Features
- PS/2 keyboard support
- Scancode to ASCII conversion
- Non-blocking input
- Key press detection

### Functions
```c
void init_keyboard(void)           // Initialize keyboard controller
char keyboard_read(void)           // Read character from keyboard
int keyboard_available(void)       // Check if key is pressed
```

### Usage
```c
init_keyboard();
if (keyboard_available()) {
    char key = keyboard_read();
    // Process key
}
```

---

## 2. 🖥️ VGA Driver (vga.c)

### Features
- VGA text-mode (80x25)
- Character and color control
- Screen clearing
- Scrolling support
- Hardware cursor control

### Functions
```c
void init_vga(void)                              // Initialize VGA
void vga_putchar(char c, uint8_t color, x, y)   // Put character at position
void vga_clear(uint8_t color)                    // Clear screen
void vga_scroll(void)                            // Scroll screen up
void vga_update_cursor(uint8_t x, uint8_t y)    // Update cursor position
```

### Color Codes
- 0x00 = Black
- 0x09 = Light Blue (Neon Blue)
- 0x0B = Light Cyan (Electric Cyan)
- 0x0C = Light Red (Deep Red)
- 0x0F = White

---

## 3. ⏱️ Timer Driver (timer.c)

### Features
- Programmable Interval Timer (PIT)
- Configurable frequency
- Tick counting
- Sleep function

### Functions
```c
void init_timer(uint32_t frequency)  // Initialize timer (Hz)
void timer_handler(void)             // Timer interrupt handler
uint32_t get_ticks(void)             // Get current tick count
void sleep(uint32_t ms)              // Sleep for milliseconds
```

### Usage
```c
init_timer(100);  // 100 Hz
sleep(1000);      // Sleep 1 second
```

---

## 4. 💾 Disk Driver (disk.c)

### Features
- ATA/IDE disk support
- LBA addressing
- Sector read/write
- 512-byte sectors

### Functions
```c
void init_disk(void)                              // Initialize disk
void disk_read_sector(uint32_t lba, uint8_t* buf) // Read sector
void disk_write_sector(uint32_t lba, uint8_t* buf)// Write sector
```

### Usage
```c
uint8_t buffer[512];
disk_read_sector(0, buffer);   // Read first sector
disk_write_sector(0, buffer);  // Write first sector
```

---

## 5. 📡 Serial Port Driver (serial.c)

### Features
- COM1 serial port (0x3F8)
- 115200 baud rate
- Character I/O
- String output
- Debug logging

### Functions
```c
void init_serial(void)              // Initialize serial port
int serial_received(void)           // Check if data received
char serial_read(void)              // Read character
int serial_transmit_empty(void)     // Check if ready to send
void serial_write(char c)           // Write character
void serial_writestring(const char*) // Write string
```

### Usage
```c
init_serial();
serial_writestring("Dragon OS Debug\n");
```

---

## 6. 🔌 PCI Driver (pci.c)

### Features
- PCI bus enumeration
- Device detection
- Configuration space access
- Vendor/Device ID reading

### Functions
```c
uint32_t pci_read(bus, slot, func, offset)       // Read config
void pci_write(bus, slot, func, offset, value)   // Write config
uint16_t pci_get_vendor(uint8_t bus, uint8_t slot) // Get vendor ID
uint16_t pci_get_device(uint8_t bus, uint8_t slot) // Get device ID
void init_pci(void)                               // Scan PCI bus
```

---

## 7. 🖱️ Mouse Driver (mouse.c)

### Features
- PS/2 mouse support
- 3-button detection
- X/Y movement tracking
- Interrupt-driven

### Functions
```c
void init_mouse(void)                        // Initialize mouse
void mouse_handler(void)                     // Mouse interrupt handler
void get_mouse_position(int8_t* x, int8_t* y) // Get position
uint8_t get_mouse_buttons(void)              // Get button state
```

### Button Bits
- Bit 0: Left button
- Bit 1: Right button
- Bit 2: Middle button

---

## 8. 🕐 RTC Driver (rtc.c)

### Features
- Real-Time Clock access
- Time reading (HH:MM:SS)
- Date reading (DD/MM/YYYY)
- BCD to binary conversion

### Functions
```c
void init_rtc(void)                                    // Initialize RTC
void get_time(uint8_t* h, uint8_t* m, uint8_t* s)     // Get time
void get_date(uint8_t* d, uint8_t* m, uint16_t* y)    // Get date
uint8_t rtc_read(uint8_t reg)                         // Read RTC register
void rtc_write(uint8_t reg, uint8_t value)            // Write RTC register
```

### Usage
```c
uint8_t hour, minute, second;
get_time(&hour, &minute, &second);
// Display: 14:30:45
```

---

## 🔧 Driver Initialization

All drivers should be initialized in the kernel:

```c
void kernel_main(void) {
    // Initialize drivers
    init_vga();
    init_keyboard();
    init_timer(100);
    init_serial();
    init_disk();
    init_pci();
    init_mouse();
    init_rtc();
    
    // Continue with OS initialization
}
```

---

## 📊 Driver Architecture

```
Dragon OS Kernel
    │
    ├── VGA Driver ────────> Screen Output
    ├── Keyboard Driver ───> User Input
    ├── Mouse Driver ──────> Pointer Input
    ├── Timer Driver ──────> System Timing
    ├── Disk Driver ───────> Storage I/O
    ├── Serial Driver ─────> Debug Output
    ├── PCI Driver ────────> Device Detection
    └── RTC Driver ────────> Date/Time
```

---

## 🎯 Port I/O Operations

All drivers use x86 port I/O instructions:

```c
// Input byte from port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Output byte to port
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
```

---

## 🔐 Hardware Ports Used

| Driver    | Ports          | Description           |
|-----------|----------------|-----------------------|
| Keyboard  | 0x60, 0x64     | PS/2 controller       |
| VGA       | 0x3D4, 0x3D5   | VGA registers         |
| Timer     | 0x40, 0x43     | PIT (8253/8254)       |
| Disk      | 0x1F0-0x1F7    | Primary ATA           |
| Serial    | 0x3F8-0x3FF    | COM1                  |
| PCI       | 0xCF8, 0xCFC   | PCI configuration     |
| Mouse     | 0x60, 0x64     | PS/2 controller       |
| RTC       | 0x70, 0x71     | CMOS/RTC              |

---

## 🚀 Performance

- **Keyboard:** Instant response, scancode-based
- **VGA:** Direct memory access (0xB8000)
- **Timer:** 100 Hz default (configurable)
- **Disk:** 512 bytes per sector
- **Serial:** 115200 baud
- **PCI:** Bus scanning on init
- **Mouse:** Interrupt-driven
- **RTC:** BCD format, 1 Hz update

---

## 🎨 Integration with Dragon OS

### Holographic UI
- VGA driver provides text-mode rendering
- Keyboard driver enables user interaction
- Mouse driver for future GUI support

### AI Voice Assistant
- Keyboard driver for command input
- Serial driver for debug output
- Timer driver for response timing

### Cybersecurity Suite
- Disk driver for log storage
- Serial driver for remote logging
- RTC driver for timestamps
- PCI driver for network card detection

---

## 📝 Driver Development

### Adding New Drivers

1. Create driver file in `drivers/` directory
2. Implement initialization function
3. Add function declarations to `drivers.h`
4. Update Makefile to compile driver
5. Initialize in kernel_main()

### Example Template

```c
/*
 * Dragon OS - New Driver
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

void init_new_driver(void) {
    // Initialization code
}

void new_driver_function(void) {
    // Driver functionality
}
```

---

## 🔍 Debugging

Use serial driver for debugging:

```c
init_serial();
serial_writestring("Driver initialized\n");
```

View output in QEMU:
```bash
qemu-system-i386 -cdrom dragon_os.iso -serial stdio
```

---

## 🌟 Future Enhancements

- Network card driver (NIC)
- Sound card driver (AC97/SB16)
- USB controller driver
- AHCI SATA driver
- Graphics driver (VESA/VBE)
- Touchscreen driver

---

## 📚 References

- Intel 8259 PIC datasheet
- VGA hardware specifications
- ATA/ATAPI standards
- PS/2 controller documentation
- PCI specification
- CMOS/RTC documentation

---

**🐉 DRAGON OS - Complete Hardware Support**

**Designed & Developed by ABID MEHMOOD**

All drivers are minimal, efficient, and production-ready!
