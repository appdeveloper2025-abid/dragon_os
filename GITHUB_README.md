# 🐉 DRAGON OS

**A Complete Bootable Operating System with Futuristic UI, AI Assistant, and Cybersecurity Tools**

**Designed & Developed by ABID MEHMOOD**

[![Build Dragon OS ISO](https://github.com/YOUR_USERNAME/dragon_os/actions/workflows/build.yml/badge.svg)](https://github.com/YOUR_USERNAME/dragon_os/actions/workflows/build.yml)

---

## 🚀 Quick Start

### Download Pre-Built ISO (Easiest)

1. Go to [Releases](https://github.com/YOUR_USERNAME/dragon_os/releases)
2. Download `dragon_os.iso`
3. Use [Rufus](https://rufus.ie/) to create bootable USB
4. Boot from USB

### Build from Source

```bash
git clone https://github.com/YOUR_USERNAME/dragon_os.git
cd dragon_os
./build.sh
grub-mkrescue -o dragon_os.iso iso
```

---

## ✨ Features

- 🎨 **Holographic Glass-Morphic UI** - Futuristic transparent interface
- 🤖 **JARVIS AI Voice Assistant** - Intelligent voice commands
- 🔐 **Cybersecurity Suite** - Network scanning, port scanning, IDS
- 💾 **8 Hardware Drivers** - Keyboard, VGA, Timer, Disk, Serial, PCI, Mouse, RTC
- 💿 **Live Boot Mode** - Run from USB without installation
- 🎯 **Complete OS** - Bootloader, Kernel, Drivers, UI, Modules

---

## 📦 What's Included

- **Bootloader** (Assembly) - GRUB multiboot
- **Kernel** (C) - Custom OS kernel
- **Drivers** (8 drivers) - Complete hardware support
- **UI Engine** - Holographic interface
- **AI Module** - Voice assistant
- **Security Suite** - Penetration testing tools
- **System Modules** - File manager, terminal, monitor

---

## 🛠️ Build Requirements

- NASM (assembler)
- GCC (compiler)
- Make
- GRUB tools (grub-mkrescue)
- xorriso

### Install on Ubuntu/Debian:
```bash
sudo apt-get install nasm gcc make binutils grub-pc-bin xorriso
```

---

## 📖 Documentation

- [README.md](README.md) - Main documentation
- [INSTALL.md](INSTALL.md) - Installation guide
- [FEATURES.md](FEATURES.md) - Feature documentation
- [DRIVERS.md](DRIVERS.md) - Driver documentation
- [CHROMEBOOK_GUIDE.md](CHROMEBOOK_GUIDE.md) - Limited storage guide

---

## 🎯 GitHub Actions

This repository includes automatic ISO building:

1. Push code to GitHub
2. GitHub Actions automatically builds ISO
3. Download from Actions artifacts or Releases

---

## 💿 Create Bootable USB

### Windows (Rufus):
1. Download [Rufus](https://rufus.ie/)
2. Select `dragon_os.iso`
3. Select USB drive
4. Click START

### Linux:
```bash
sudo dd if=dragon_os.iso of=/dev/sdX bs=4M status=progress
sync
```

---

## 🖥️ System Requirements

**Minimum:**
- CPU: x86 compatible
- RAM: 512 MB
- Storage: 100 MB for ISO
- Display: VGA compatible

---

## 📊 Project Structure

```
dragon_os/
├── .github/workflows/    # GitHub Actions
├── boot/                 # Bootloader
├── kernel/               # OS kernel
├── drivers/              # Hardware drivers (8 drivers)
├── ui/                   # UI engine
├── modules/              # System modules
├── iso/boot/grub/        # GRUB config
├── build.sh              # Build script
├── Makefile              # Build automation
└── README.md             # This file
```

---

## 🎨 Screenshots

Dragon OS features:
- Animated boot screen with Dragon logo
- Holographic control hub
- Security dashboard
- AI assistant panel
- System monitor
- Terminal interface

---

## 🤝 Contributing

This is a personal project showcasing OS development skills.

---

## 📝 License

Custom OS Project - All rights reserved © ABID MEHMOOD

---

## 🌟 Highlights

- ✅ Complete bootable OS from scratch
- ✅ 8 hardware drivers
- ✅ Futuristic holographic UI
- ✅ AI voice assistant
- ✅ Cybersecurity tools
- ✅ Live boot mode
- ✅ Professional documentation
- ✅ GitHub Actions CI/CD

---

**🐉 DRAGON OS - The Future of Operating Systems**

**Designed & Developed by ABID MEHMOOD**

Version 1.0 - Live Operating System
