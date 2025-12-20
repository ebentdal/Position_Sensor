# -------- Project --------
BUILD_DIR := build
SRC_DIR   := src
INC_DIR   := headers

# -------- MCU / Clock --------
MCU     := atmega168
F_CPU   := 8000000UL

# -------- Programmer (Arduino as ISP running ArduinoISP sketch) --------
AVRDUDE_MCU := m168
PROGRAMMER  := stk500v1
PORT        := /dev/cu.usbmodem101
BAUD        := 19200
AVRDUDECONF := /opt/homebrew/etc/avrdude.conf

# -------- Toolchain (Arduino15 packaged) --------
ARDUINO_AVR_TOOLS := $(HOME)/Library/Arduino15/packages/arduino/tools
AVR_GCC_BIN := $(ARDUINO_AVR_TOOLS)/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin

CXX     := $(AVR_GCC_BIN)/avr-g++
OBJCOPY := $(AVR_GCC_BIN)/avr-objcopy
SIZE    := $(AVR_GCC_BIN)/avr-size
AVRDUDE := avrdude

# -------- Sources --------
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

ELF := $(BUILD_DIR)/main.elf
HEX := $(BUILD_DIR)/main.hex

# -------- Flags --------
CXXFLAGS := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra \
            -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections \
            -I$(INC_DIR)

LDFLAGS  := -Wl,--gc-sections

# -------- Targets --------
.PHONY: all clean flash info

all: $(HEX)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link (IMPORTANT: link from OBJ, not from a .cpp)
$(ELF): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Hex
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
