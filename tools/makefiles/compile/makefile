################################################################################

SHELL = bash

NUM_CPU = $(shell nproc --all)

MAKEFLAGS += -rR						# do not use make's built-in rules and variables
MAKEFLAGS += -j$(NUM_CPU)				# parallel processing
MAKEFLAGS += -k							# keep going
MAKEFLAGS += --warn-undefined-variables

ECHO = echo -e
RM   = rm -rf

ifeq ("$(origin VERBOSE)", "command line")
	Q =
else
	Q = @
endif

################################################################################

PROJECT_NAME = $(notdir $(CURDIR))

$(info )
$(info PROJECT=$(PROJECT_NAME))
$(info )

SOURCE_DIR = src
OBJECT_DIR = obj
OUTPUT_DIR = out

SRC_FILE_EXTS = .asm .c .cpp

################################################################################

REPO_ROOT = $(shell git rev-parse --show-toplevel)

################################################################################

board ?= TEENSY40

ifeq ($(board),TEENSY40)
MCU = IMXRT1062
MCU_LD = imxrt1062.ld
else ifeq ($(board),TEENSY41)
MCU = IMXRT1062
MCU_LD = imxrt1062_t41.ld
else
$(error [error] Unsupported board: $(board))
endif

################################################################################

ELF_FILE = $(OUTPUT_DIR)/$(PROJECT_NAME).elf
MAP_FILE = $(OUTPUT_DIR)/$(PROJECT_NAME).map
HEX_FILE = $(OUTPUT_DIR)/$(PROJECT_NAME).hex
BIN_FILE = $(OUTPUT_DIR)/$(PROJECT_NAME).bin
DIS_FILE = $(OUTPUT_DIR)/$(PROJECT_NAME).dis

LINKER_FILE_PATH :=	$(sort $(shell find -L $(SOURCE_DIR) -type f -name '*.ld' -printf '%h\n'))
LINKER_FILE       = $(LINKER_FILE_PATH)/$(MCU_LD)

################################################################################

CC      = arm-none-eabi-gcc
CXX     = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size

DEFINES  = -D__$(MCU)__
DEFINES += -DARDUINO=10813
DEFINES += -DARDUINO_$(board)
DEFINES += -DF_CPU=600000000
DEFINES += -DLAYOUT_US_ENGLISH
DEFINES += -DTEENSYDUINO=154
DEFINES += -DUSB_SERIAL
DEFINES += -DUSING_MAKEFILE

# common MCU options
CPUFLAGS  = -mcpu=cortex-m7
CPUFLAGS += -mfloat-abi=hard
CPUFLAGS += -mfpu=fpv5-d16
CPUFLAGS += -mthumb

# common compiler options for C and C++
CPPFLAGS  = $(CPUFLAGS)
CPPFLAGS += $(DEFINES)
CPPFLAGS += $(INCLUDE_DIRS)
CPPFLAGS += -c					# compile and assemble, do not link
CPPFLAGS += -fdata-sections
CPPFLAGS += -ffunction-sections
CPPFLAGS += -g
CPPFLAGS += -MMD				# generate dependency file
CPPFLAGS += -Ofast
CPPFLAGS += -Wall
CPPFLAGS += -Werror
CPPFLAGS += -Wno-narrowing

# compiler options for C only
CFLAGS  = -std=gnu11
CFLAGS += -x c

# compiler options for C++ only
CXXFLAGS  = -std=gnu++17
CXXFLAGS += -felide-constructors
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti
CXXFLAGS += -Wno-address-of-packed-member
CXXFLAGS += -Wno-register
CXXFLAGS += -Wno-stringop-truncation
CXXFLAGS += -Wno-unused-local-typedefs
CXXFLAGS += -Wno-unused-value
CXXFLAGS += -x c++

LDFLAGS  = $(CPUFLAGS)
LDFLAGS += -Ofast
LDFLAGS += -T$(LINKER_FILE)
LDFLAGS += -Wl,--gc-sections,--defsym=__rtc_localtime=0,-Map=$(MAP_FILE)

# additional libraries to link
LIBS  = -lm
LIBS += -lstdc++

HEX_FLAGS  = -O ihex
HEX_FLAGS += -R .eeprom

BIN_FLAGS  = -O binary
BIN_FLAGS += -R .eeprom

DIS_FLAGS  = --all

################################################################################

FLASHER = $(REPO_ROOT)/tools/teensy_loader_cli/teensy_loader_cli

FLASHER_FLAGS  = --mcu=$(MCU)
FLASHER_FLAGS += -w				# wait for device
FLASHER_FLAGS += -v				# verbose
FLASHER_FLAGS += -s				# send soft reboot command

################################################################################

PICOCOM = picocom

dev  ?= /dev/ttyACMO
baud ?= 115200

PICOCOM_FLAGS  = --baud $(baud)
PICOCOM_FLAGS += --echo
PICOCOM_FLAGS += --imap lfcrlf
PICOCOM_FLAGS += --omap crlf
PICOCOM_FLAGS += --emap crlf

################################################################################

INCLUDE_DIRS	:=	$(addprefix -I,						\
					$(sort $(shell find -L $(SOURCE_DIR) -type d)))

OBJS			:=	$(sort								\
					$(addprefix $(OBJECT_DIR)/,			\
					$(addsuffix .o,						\
					$(basename							\
					$(foreach ext, $(SRC_FILE_EXTS),	\
					$(shell test -d $(SOURCE_DIR) && find -L $(SOURCE_DIR) -type f -name *$(ext) -printf '%P\n'))))))

################################################################################

.PHONY: all help clean rebuild flash reset serial
.SECONDARY: $(OBJS)

all: $(ELF_FILE) $(HEX_FILE) $(BIN_FILE) $(DIS_FILE)

help:
	@$(ECHO)
	@$(ECHO) 'make                    - build project'
	@$(ECHO) '    verbose=<true>      - optional, default is false'
	@$(ECHO) '    board=<board>       - optional, default is $(board)'
	@$(ECHO)
	@$(ECHO) 'make flash              - flash hex file to teensy board'
	@$(ECHO) '    board=<board>       - optional, default is $(board)'
	@$(ECHO)
	@$(ECHO) 'make reset              - reset teensy board'
	@$(ECHO) '    board=<board>       - optional, default is $(board)'
	@$(ECHO)
	@$(ECHO) 'make serial             - start picocom to communicate with teensy'
	@$(ECHO) '    dev=<device>        - optional, default is /dev/ttyACM0'
	@$(ECHO) '    baud=<baud>         - optional, default is 115200'
	@$(ECHO)
	@$(ECHO) 'make clean              - clean object & output files'
	@$(ECHO)
	@$(ECHO) 'make rebuild            - clean & make'
	@$(ECHO)
	@$(ECHO) 'make help               - this menu'
	@$(ECHO)



$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.asm
	@    $(ECHO) "(ASM)" $<
	@    mkdir -p $(@D)
	$(Q) $(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@    $(ECHO) "(CC) " $<
	@    mkdir -p $(@D)
	$(Q) $(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@    $(ECHO) "(CXX)" $<
	@    mkdir -p $(@D)
	$(Q) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

$(ELF_FILE): $(OBJS) $(LINKER_FILE)
	@    $(ECHO) "\n(LINK)" $@ "\n"
	@    mkdir -p $(@D)
	$(Q) $(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
	$(Q) $(SIZE) $@
	@    $(ECHO)



%.hex: %.elf
	@    $(ECHO) "(HEX) " $@
	$(Q) $(OBJCOPY) $(HEX_FLAGS) $< $@

%.bin: %.elf
	@    $(ECHO) "(BIN) " $@
	$(Q) $(OBJCOPY) $(BIN_FLAGS) $< $@

%.dis: %.elf
	@    $(ECHO) "(DIS) " $@
	$(Q) $(OBJDUMP) $(DIS_FLAGS) $< > $@



flash: $(HEX_FILE)
	$(Q) $(FLASHER) $(FLASHER_FLAGS) $<

reset:
	$(Q) $(FLASHER) $(FLASHER_FLAGS) -b



serial:
	$(PICOCOM) /dev/ttyACM0 $(PICOCOM_FLAGS)



clean:
	$(RM) $(OUTPUT_DIR) $(OBJECT_DIR)
	@     $(ECHO) 'Finished clean\n'

rebuild: clean
	$(Q) $(MAKE) -s all



-include $(OBJS:.o=.d) # compiler generated dependency info
