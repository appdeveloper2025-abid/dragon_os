# Dragon OS Makefile
# Designed & Developed by ABID MEHMOOD

AS = nasm
CC = gcc
LD = ld

ASFLAGS = -f elf32
CFLAGS = -m32 -c -ffreestanding -O2 -Wall -Wextra -fno-exceptions -nostdlib -nostdinc
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

BOOT_SRC = boot/boot.asm
KERNEL_SRC = kernel/kernel.c
UI_SRC = ui/ui_engine.c
VOICE_SRC = modules/voice_module.c
SECURITY_SRC = modules/security_module.c
DRIVER_SRCS = drivers/keyboard.c drivers/vga.c drivers/timer.c drivers/disk.c drivers/serial.c drivers/pci.c drivers/mouse.c drivers/rtc.c

BOOT_OBJ = boot/boot.o
KERNEL_OBJ = kernel/kernel.o
UI_OBJ = ui/ui_engine.o
VOICE_OBJ = modules/voice_module.o
SECURITY_OBJ = modules/security_module.o
DRIVER_OBJS = drivers/keyboard.o drivers/vga.o drivers/timer.o drivers/disk.o drivers/serial.o drivers/pci.o drivers/mouse.o drivers/rtc.o

OBJS = $(BOOT_OBJ) $(KERNEL_OBJ) $(UI_OBJ) $(VOICE_OBJ) $(SECURITY_OBJ) $(DRIVER_OBJS)

KERNEL_BIN = dragon_os.bin
ISO_DIR = iso
ISO_FILE = dragon_os.iso

.PHONY: all clean iso run

all: $(KERNEL_BIN)

$(BOOT_OBJ): $(BOOT_SRC)
	$(AS) $(ASFLAGS) $(BOOT_SRC) -o $(BOOT_OBJ)

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) $(KERNEL_SRC) -o $(KERNEL_OBJ)

$(UI_OBJ): $(UI_SRC)
	$(CC) $(CFLAGS) $(UI_SRC) -o $(UI_OBJ)

$(VOICE_OBJ): $(VOICE_SRC)
	$(CC) $(CFLAGS) $(VOICE_SRC) -o $(VOICE_OBJ)

$(SECURITY_OBJ): $(SECURITY_SRC)
	$(CC) $(CFLAGS) $(SECURITY_SRC) -o $(SECURITY_OBJ)

drivers/%.o: drivers/%.c
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJS)

iso: $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/$(KERNEL_BIN)
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)

run: iso
	qemu-system-i386 -cdrom $(ISO_FILE) -m 512M

clean:
	rm -f $(OBJS) $(KERNEL_BIN) $(ISO_FILE)
	rm -rf $(ISO_DIR)/boot/*.bin

help:
	@echo "Dragon OS Build System"
	@echo "======================"
	@echo "make          - Build Dragon OS kernel"
	@echo "make iso      - Create bootable ISO"
	@echo "make run      - Run in QEMU emulator"
	@echo "make clean    - Clean build files"
