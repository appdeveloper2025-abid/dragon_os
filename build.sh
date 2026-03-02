#!/bin/bash
# Dragon OS Build Script for Linux/Unix
# Designed & Developed by ABID MEHMOOD

echo "========================================"
echo "   DRAGON OS BUILD SYSTEM"
echo "   Designed by ABID MEHMOOD"
echo "========================================"
echo ""

# Check for required tools
command -v nasm >/dev/null 2>&1 || { echo "[ERROR] NASM not found. Install: sudo apt-get install nasm"; exit 1; }
command -v gcc >/dev/null 2>&1 || { echo "[ERROR] GCC not found. Install: sudo apt-get install gcc"; exit 1; }
command -v ld >/dev/null 2>&1 || { echo "[ERROR] LD not found. Install: sudo apt-get install binutils"; exit 1; }

echo "[*] Building Dragon OS..."
echo ""

# Create directories
mkdir -p iso/boot/grub

# Assemble bootloader
echo "[1/5] Assembling bootloader..."
nasm -f elf32 boot/boot.asm -o boot/boot.o || { echo "[ERROR] Bootloader assembly failed"; exit 1; }

# Compile kernel
echo "[2/5] Compiling kernel..."
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra kernel/kernel.c -o kernel/kernel.o || { echo "[ERROR] Kernel compilation failed"; exit 1; }

# Compile UI engine
echo "[3/5] Compiling UI engine..."
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra ui/ui_engine.c -o ui/ui_engine.o

# Compile modules
echo "[4/6] Compiling modules..."
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra modules/voice_module.c -o modules/voice_module.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra modules/security_module.c -o modules/security_module.o

# Compile drivers
echo "[5/6] Compiling drivers..."
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/keyboard.c -o drivers/keyboard.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/vga.c -o drivers/vga.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/timer.c -o drivers/timer.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/disk.c -o drivers/disk.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/serial.c -o drivers/serial.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/pci.c -o drivers/pci.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/mouse.c -o drivers/mouse.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers/rtc.c -o drivers/rtc.o

# Link kernel
echo "[6/6] Linking kernel..."
ld -m elf_i386 -T linker.ld -o dragon_os.bin boot/boot.o kernel/kernel.o ui/ui_engine.o modules/voice_module.o modules/security_module.o drivers/keyboard.o drivers/vga.o drivers/timer.o drivers/disk.o drivers/serial.o drivers/pci.o drivers/mouse.o drivers/rtc.o || { echo "[ERROR] Linking failed"; exit 1; }

# Copy kernel to ISO directory
cp dragon_os.bin iso/boot/dragon_os.bin

echo ""
echo "========================================"
echo "   BUILD SUCCESSFUL!"
echo "========================================"
echo ""
echo "Dragon OS kernel built: dragon_os.bin"
echo ""

# Check for grub-mkrescue
if command -v grub-mkrescue >/dev/null 2>&1; then
    echo "[*] Creating bootable ISO..."
    grub-mkrescue -o dragon_os.iso iso
    echo ""
    echo "Bootable ISO created: dragon_os.iso"
    echo ""
    
    # Check for QEMU
    if command -v qemu-system-i386 >/dev/null 2>&1; then
        echo "To test in QEMU, run: qemu-system-i386 -cdrom dragon_os.iso"
    else
        echo "Install QEMU to test: sudo apt-get install qemu-system-x86"
    fi
else
    echo "To create ISO, install GRUB: sudo apt-get install grub-pc-bin xorriso"
    echo "Then run: grub-mkrescue -o dragon_os.iso iso"
fi

echo ""
