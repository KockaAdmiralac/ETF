PROGRAM = aor2
BUILD_DIR = build

SOURCE_CPP_LIST = $(wildcard src/*.cpp src/**/*.cpp)
OBJECT_FILES = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_CPP_LIST:.cpp=.o)))

vpath %.cpp $(sort $(dir $(SOURCE_CPP_LIST)))

CC = g++ -c
LD = g++

FLAGS_CC =
FLAGS_CC += -Wall -Wextra
FLAGS_CC += -MMD -MP
FLAGS_CC += -march=native
FLAGS_CC += -std=c++17
FLAGS_CC += -Iinc -isystemlib
ifeq ($(NO_DEBUG), 1)
else
FLAGS_CC += -g
endif
ifeq ($(OPTIMIZED_PROCESSOR), 1)
FLAGS_CC += -DOPTIMIZED_PROCESSOR
endif

all: $(BUILD_DIR)/$(PROGRAM)

$(BUILD_DIR)/$(PROGRAM): $(OBJECT_FILES)
	$(LD) -o $(@) $(OBJECT_FILES)

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CC) $(FLAGS_CC) -o $(@) $(<)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)
