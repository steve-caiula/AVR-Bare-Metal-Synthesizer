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
all: main.hex

# Compile C source from the src folder
main.bin: src/main.c include/pitches.h
	$(CC) $(CFLAGS) -o main.bin src/main.c

# Convert binary to Intel HEX format
main.hex: main.bin
	$(OBJCOPY) -O ihex main.bin main.hex

# Upload the HEX file to the Arduino board
flash: main.hex
	$(AVRDUDE) -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD) -U flash:w:main.hex:i

# Clean up build artifacts
clean:
	del main.bin main.hex