PROJECT   := position_sensor
SRC       := src/main.cpp
BUILD_DIR := build

MCU       := atmega168
AVRDUDE_MCU := m168

PROGRAMMER := stk500v1
PORT       := /dev/cu.usbmodem101
BAUD       := 19200


F_CPU     := 8000000UL


ARDUINO_AVR_TOOLS := $(HOME)/Library/Arduino15/packages/arduino/tools
AVR_GCC_BIN := $(ARDUINO_AVR_TOOLS)/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin

CXX      := $(AVR_GCC_BIN)/avr-g++
OBJCOPY  := $(AVR_GCC_BIN)/avr-objcopy
SIZE     := $(AVR_GCC_BIN)/avr-size

AVRDUDE  := avrdude
AVRDUDECONF := /opt/homebrew/etc/avrdude.conf

# -------- Flags --------
CXXFLAGS := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra \
            -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections
LDFLAGS  := -Wl,--gc-sections

# -------- Targets --------
ELF := $(BUILD_DIR)/main.elf
HEX := $(BUILD_DIR)/main.hex

.PHONY: all clean flash info size

all: $(HEX)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ELF): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@
	$(SIZE) --format=avr --mcu=$(MCU) $<

flash: $(HEX)
	$(AVRDUDE) -C$(AVRDUDECONF) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -p $(AVRDUDE_MCU) \
		-U flash:w:$<:i

info:
	$(AVRDUDE) -C$(AVRDUDECONF) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -p $(AVRDUDE_MCU) -v

clean:
	rm -rf $(BUILD_DIR)
