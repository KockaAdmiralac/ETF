PROGRAM = program
BUILD_DIR = build
DEBUG_ENABLED = 1

SOURCE_C_LIST = \
	src/main.c \
	src/test.c

SOURCE_S_LIST = \
	src/startup.s

INCLUDE_LIST = -Iinc

CC = arm-none-eabi-gcc -c
AS = arm-none-eabi-gcc -c -x assembler
LD = arm-none-eabi-ld
HX = arm-none-eabi-objcopy -O ihex

LINKER_SCRIPT = linker_script.ld

OBJECTS_LIST =
OBJECTS_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_C_LIST:.c=.o)))
OBJECTS_LIST += $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_S_LIST:.s=.o)))
vpath %.c $(sort $(dir $(SOURCE_C_LIST)))
vpath %.s $(sort $(dir $(SOURCE_S_LIST)))

MCU = -mcpu=cortex-m3 -mthumb
FLAGS_DEBUG = -g -gdwarf-2 -fdebug-prefix-map==../
WARNINGS = -Wall -Wextra

FLAGS_AS =
FLAGS_AS += $(MCU)
FLAGS_AS += $(WARNINGS)
ifeq ($(DEBUG_ENABLED), 1)
FLAGS_AS += $(FLAGS_DEBUG)
endif
FLAGS_AS += -mlong-calls

	FLAGS_CC =
FLAGS_CC += $(MCU)
FLAGS_CC += $(WARNINGS)
FLAGS_CC += $(INCLUDE_LIST)
ifeq ($(DEBUG_ENABLED), 1)
FLAGS_CC += $(FLAGS_DEBUG)
endif
FLAGS_CC += -MMD -MP
FLAGS_CC += -mlong-calls

all: $(BUILD_DIR)/$(PROGRAM).elf $(BUILD_DIR)/$(PROGRAM).hex

$(BUILD_DIR)/$(PROGRAM).hex: $(BUILD_DIR)/$(PROGRAM).elf
	$(HX) $(<) $(@)

$(BUILD_DIR)/$(PROGRAM).elf: $(OBJECTS_LIST) $(LINKER_SCRIPT)
	$(LD) -T $(LINKER_SCRIPT) -o $(@) $(OBJECTS_LIST)

$(BUILD_DIR)/%.o: %.s makefile | $(BUILD_DIR)
	$(AS) $(FLAGS_AS) -o $(@) $(<)

$(BUILD_DIR)/%.o: %.c makefile | $(BUILD_DIR)
	$(CC) $(FLAGS_CC) -o $(@) $(<)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)


-include $(wildcard $(BUILD_DIR)/*.d)
