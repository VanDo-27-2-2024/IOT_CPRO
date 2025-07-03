# Toolchain configuration for Linux
CC = gcc
LD = gcc
RM = rm -f
MKDIR = mkdir -p

# Project structure
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
TARGET = spws_controller

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) \

LDFLAGS = -Wl,--gc-sections -lm

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(wildcard $(INC_DIR)/*.h)

.PHONY: all clean run debug

all: $(BIN_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	@echo "Build successful. Binary size:"
	@size $@

$(BUILD_DIR) $(BIN_DIR):
	$(MKDIR) $@

clean:
	$(RM) -r $(BUILD_DIR) $(BIN_DIR)

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

debug: $(BIN_DIR)/$(TARGET)
	gdb ./$(BIN_DIR)/$(TARGET)
