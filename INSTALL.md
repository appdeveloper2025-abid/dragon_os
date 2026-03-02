# 🐉 DRAGON OS - Installation & Setup Guide

**Designed & Developed by ABID MEHMOOD**

---

## 📋 Table of Contents

1. [System Requirements](#system-requirements)
2. [Installing Build Tools](#installing-build-tools)
3. [Building Dragon OS](#building-dragon-os)
4. [Creating Bootable Media](#creating-bootable-media)
5. [Running Dragon OS](#running-dragon-os)
6. [Troubleshooting](#troubleshooting)

---

## 💻 System Requirements

### Minimum Requirements
- **CPU:** x86 compatible processor (Intel/AMD)
- **RAM:** 512 MB
- **Storage:** 100 MB for ISO file
- **Display:** VGA compatible monitor

### Recommended Requirements
- **CPU:** Intel Core i3 or AMD equivalent
- **RAM:** 1 GB or more
- **Storage:** 500 MB free space
- **Display:** 1024x768 resolution or higher

---

## 🛠️ Installing Build Tools

### For Ubuntu/Debian Linux:

```bash
# Update package list
sudo apt-get update

# Install required tools
sudo apt-get install -y nasm gcc make binutils grub-pc-bin xorriso qemu-system-x86

# Verify installations
nasm --version
gcc --version
grub-mkrescue --version
qemu-system-i386 --version
```

### For Fedora/RHEL/CentOS:

```bash
# Install required tools
sudo dnf install -y nasm gcc make binutils grub2-tools xorriso qemu-system-x86

# Verify installations
nasm --version
gcc --version
```

### For Arch Linux:

```bash
# Install required tools
sudo pacman -S nasm gcc make binutils grub xorriso qemu

# Verify installations
nasm --version
gcc --version
```

### For Windows:

**Option 1: Using WSL (Recommended)**

1. Install WSL2:
```powershell
wsl --install
```

2. Open Ubuntu in WSL and follow Ubuntu instructions above

**Option 2: Using MinGW/MSYS2**

1. Download and install MSYS2 from: https://www.msys2.org/
2. Open MSYS2 terminal and run:
```bash
pacman -S mingw-w64-x86_64-gcc nasm make
```

**Option 3: Using Cygwin**

1. Download Cygwin from: https://www.cygwin.com/
2. During installation, select: gcc, nasm, make, binutils

---

## 🔨 Building Dragon OS

### Method 1: Using Build Scripts (Easiest)

**On Linux/Unix:**
```bash
cd dragon_os
chmod +x build.sh
./build.sh
```

**On Windows:**
```cmd
cd dragon_os
build.bat
```

### Method 2: Using Makefile

```bash
cd dragon_os

# Build kernel
make

# Create ISO
make iso

# Test in QEMU
make run

# Clean build files
make clean
```

### Method 3: Manual Build

```bash
cd dragon_os

# Create directories
mkdir -p iso/boot/grub

# Assemble bootloader
nasm -f elf32 boot/boot.asm -o boot/boot.o

# Compile kernel
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra kernel/kernel.c -o kernel/kernel.o

# Compile UI engine
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra ui/ui_engine.c -o ui/ui_engine.o

# Compile modules
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra modules/voice_module.c -o modules/voice_module.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra modules/security_module.c -o modules/security_module.o

# Link everything
ld -m elf_i386 -T linker.ld -o dragon_os.bin boot/boot.o kernel/kernel.o ui/ui_engine.o modules/voice_module.o modules/security_module.o

# Copy to ISO directory
cp dragon_os.bin iso/boot/dragon_os.bin

# Create bootable ISO
grub-mkrescue -o dragon_os.iso iso
```

---

## 💿 Creating Bootable Media

### Creating Bootable USB (Linux)

```bash
# Find your USB device (e.g., /dev/sdb)
lsblk

# Write ISO to USB (CAUTION: This will erase USB data!)
sudo dd if=dragon_os.iso of=/dev/sdX bs=4M status=progress
sudo sync

# Replace /dev/sdX with your actual USB device
```

### Creating Bootable USB (Windows)

**Using Rufus:**
1. Download Rufus from: https://rufus.ie/
2. Insert USB drive
3. Open Rufus
4. Select dragon_os.iso
5. Click "START"

**Using Etcher:**
1. Download Etcher from: https://www.balena.io/etcher/
2. Insert USB drive
3. Open Etcher
4. Select dragon_os.iso
5. Select USB drive
6. Click "Flash"

---

## 🚀 Running Dragon OS

### Option 1: Virtual Machine (Recommended for Testing)

**Using QEMU:**
```bash
# Basic run
qemu-system-i386 -cdrom dragon_os.iso

# With more memory
qemu-system-i386 -cdrom dragon_os.iso -m 512M

# With acceleration (Linux)
qemu-system-i386 -cdrom dragon_os.iso -m 512M -enable-kvm
```

**Using VirtualBox:**
1. Open VirtualBox
2. Click "New"
3. Name: Dragon OS
4. Type: Other
5. Version: Other/Unknown
6. Memory: 512 MB or more
7. Skip hard disk creation
8. Go to Settings → Storage
9. Add dragon_os.iso as CD/DVD
10. Start VM

**Using VMware:**
1. Open VMware
2. Create New Virtual Machine
3. Select "I will install the operating system later"
4. Guest OS: Other → Other
5. Allocate 512 MB RAM
6. Skip disk creation
7. Edit VM settings → CD/DVD → Use ISO image → Select dragon_os.iso
8. Power on VM

### Option 2: Real Hardware

1. Create bootable USB (see above)
2. Insert USB into computer
3. Restart computer
4. Press Boot Menu key (usually F12, F2, DEL, or ESC)
5. Select USB device from boot menu
6. Dragon OS will load automatically

---

## 🔧 Troubleshooting

### Build Errors

**Error: "nasm: command not found"**
- Solution: Install NASM using your package manager

**Error: "gcc: command not found"**
- Solution: Install GCC compiler

**Error: "cannot find -lgcc"**
- Solution: Install 32-bit libraries:
  ```bash
  sudo apt-get install gcc-multilib
  ```

**Error: "grub-mkrescue: command not found"**
- Solution: Install GRUB tools:
  ```bash
  sudo apt-get install grub-pc-bin xorriso
  ```

### Boot Errors

**Error: "No bootable device"**
- Solution: Ensure USB is properly created and boot order is correct in BIOS

**Error: "GRUB error"**
- Solution: Recreate ISO with proper GRUB configuration

**Black screen after boot**
- Solution: Try different virtual machine or check VGA compatibility

### Runtime Issues

**Issue: OS boots but shows garbled text**
- Solution: This is normal for VGA text mode, ensure proper VGA support

**Issue: No response to commands**
- Solution: Current version uses simulated input, keyboard driver needed for full interaction

---

## 📝 Quick Reference

### Build Commands
```bash
make          # Build kernel
make iso      # Create ISO
make run      # Test in QEMU
make clean    # Clean build files
```

### File Structure
```
dragon_os/
├── boot/boot.asm           # Bootloader
├── kernel/kernel.c         # Main kernel
├── ui/ui_engine.c          # UI system
├── modules/                # OS modules
├── iso/boot/grub/grub.cfg  # Boot config
└── Makefile                # Build automation
```

### Testing Checklist
- [ ] Build completes without errors
- [ ] ISO file created successfully
- [ ] Boots in QEMU
- [ ] Displays Dragon OS logo
- [ ] Shows developer credit
- [ ] UI panels render correctly
- [ ] System status displays

---

## 🎯 Next Steps

After successful installation:

1. **Test in Virtual Machine** - Verify all features work
2. **Create Bootable USB** - Test on real hardware
3. **Explore Features** - Try voice commands and security tools
4. **Customize** - Modify source code to add features
5. **Share** - Show off your Dragon OS installation!

---

## 📞 Support

If you encounter issues:

1. Check this troubleshooting guide
2. Verify all build tools are installed correctly
3. Ensure system meets minimum requirements
4. Try building in a clean environment

---

## 🌟 Features to Explore

Once Dragon OS is running:

- **Holographic UI** - Transparent panels with neon borders
- **AI Assistant** - JARVIS-like voice commands
- **Security Suite** - Network scanning and monitoring
- **System Monitor** - Real-time resource tracking
- **File Manager** - Browse system files
- **Terminal** - Command-line interface

---

**🐉 DRAGON OS - The Future is Now**

**Designed & Developed by ABID MEHMOOD**

Version 1.0 - Live Operating System
