@echo off
REM Dragon OS Build Script for Windows
REM Designed & Developed by ABID MEHMOOD

echo ========================================
echo    DRAGON OS BUILD SYSTEM
echo    Designed by ABID MEHMOOD
echo ========================================
echo.

REM Check for required tools
where nasm >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] NASM not found. Please install NASM.
    exit /b 1
)

where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] GCC not found. Please install GCC.
    exit /b 1
)

echo [*] Building Dragon OS...
echo.

REM Create directories
if not exist "iso\boot\grub" mkdir iso\boot\grub

REM Assemble bootloader
echo [1/5] Assembling bootloader...
nasm -f elf32 boot\boot.asm -o boot\boot.o
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Bootloader assembly failed
    exit /b 1
)

REM Compile kernel
echo [2/5] Compiling kernel...
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra kernel\kernel.c -o kernel\kernel.o
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Kernel compilation failed
    exit /b 1
)

REM Compile UI engine
echo [3/5] Compiling UI engine...
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra ui\ui_engine.c -o ui\ui_engine.o

REM Compile modules
echo [4/6] Compiling modules...
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra modules\voice_module.c -o modules\voice_module.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra modules\security_module.c -o modules\security_module.o

REM Compile drivers
echo [5/6] Compiling drivers...
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\keyboard.c -o drivers\keyboard.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\vga.c -o drivers\vga.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\timer.c -o drivers\timer.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\disk.c -o drivers\disk.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\serial.c -o drivers\serial.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\pci.c -o drivers\pci.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\mouse.c -o drivers\mouse.o
gcc -m32 -c -ffreestanding -O2 -Wall -Wextra drivers\rtc.c -o drivers\rtc.o

REM Link kernel
echo [6/6] Linking kernel...
ld -m elf_i386 -T linker.ld -o dragon_os.bin boot\boot.o kernel\kernel.o ui\ui_engine.o modules\voice_module.o modules\security_module.o drivers\keyboard.o drivers\vga.o drivers\timer.o drivers\disk.o drivers\serial.o drivers\pci.o drivers\mouse.o drivers\rtc.o
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Linking failed
    exit /b 1
)

REM Copy kernel to ISO directory
copy dragon_os.bin iso\boot\dragon_os.bin

echo.
echo ========================================
echo    BUILD SUCCESSFUL!
echo ========================================
echo.
echo Dragon OS kernel built: dragon_os.bin
echo.
echo To create ISO, run: grub-mkrescue -o dragon_os.iso iso
echo To test in QEMU: qemu-system-i386 -cdrom dragon_os.iso
echo.

pause
