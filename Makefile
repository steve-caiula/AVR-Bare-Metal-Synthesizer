# Project parameters
MCU = atmega328p
F_CPU = 16000000UL
BAUD = 115200
PORT = COM3

# Tools definitions
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Compilation flags
# -Iinclude tells the compiler to look for header files in the include folder
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Iinclude

# Main target
all: main.hex main.bin

# 1. Link the object files into an ELF (Executable and Linkable Format) file
# This file contains debug symbols and metadata (the ~9KB file you saw)
main.elf: src/main.c include/pitches.h
	$(CC) $(CFLAGS) -o main.elf src/main.c

# 2. Extract the Intel HEX format for flashing
main.hex: main.elf
	$(OBJCOPY) -O ihex main.elf main.hex

# 3. Extract the raw binary footprint (this will be the <300 bytes file)
main.bin: main.elf
	$(OBJCOPY) -O binary main.elf main.bin

# Upload the HEX file to the Arduino board
flash: main.hex
	$(AVRDUDE) -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -U flash:w:main.hex:i

# Clean up build artifacts
clean:
	del main.elf main.hex main.bin