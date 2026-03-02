@echo off
REM Dragon OS - Minimal USB Creator
REM For users with limited storage
REM Designed & Developed by ABID MEHMOOD

echo ========================================
echo   DRAGON OS - USB Creator (Minimal)
echo   No ISO needed - Direct USB boot
echo ========================================
echo.

REM Check if USB drive letter is provided
if "%1"=="" (
    echo Usage: create_usb.bat [USB_DRIVE_LETTER]
    echo Example: create_usb.bat E:
    echo.
    echo Please provide your USB drive letter
    pause
    exit /b 1
)

set USB_DRIVE=%1

echo Creating bootable structure on %USB_DRIVE%...
echo.

REM Create directories
mkdir %USB_DRIVE%\boot 2>nul
mkdir %USB_DRIVE%\boot\grub 2>nul

REM Copy GRUB config
echo Copying GRUB configuration...
copy iso\boot\grub\grub.cfg %USB_DRIVE%\boot\grub\

REM Copy kernel (if exists)
if exist dragon_os.bin (
    echo Copying Dragon OS kernel...
    copy dragon_os.bin %USB_DRIVE%\boot\
) else (
    echo WARNING: dragon_os.bin not found!
    echo You need to build the kernel first.
)

echo.
echo ========================================
echo   USB Structure Created!
echo ========================================
echo.
echo Next steps:
echo 1. Install GRUB bootloader to USB
echo 2. Boot from USB
echo.
echo Note: You need GRUB installed on USB to boot.
echo Use Rufus or ask someone with Linux to install GRUB.
echo.
pause
