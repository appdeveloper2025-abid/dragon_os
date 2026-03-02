@echo off
echo Creating Dragon OS Bootable Structure...

REM Create bootable directory structure
mkdir bootable_usb 2>nul
mkdir bootable_usb\boot 2>nul
mkdir bootable_usb\boot\grub 2>nul

REM Copy GRUB config
copy iso\boot\grub\grub.cfg bootable_usb\boot\grub\

REM Copy kernel (you'll need to build this first)
copy dragon_os.bin bootable_usb\boot\

echo Done! Copy 'bootable_usb' folder contents directly to USB drive
pause
