MCU      = atmega328p
F_CPU    = 16000000UL
TARGET   = main
SRC      = main.c
OBJ      = $(SRC:.c=.o)

CC       = avr-gcc
OBJCOPY  = avr-objcopy
CFLAGS   = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -std=gnu11
LDFLAGS  = -mmcu=$(MCU)

all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex

.PHONY: all clean