# Define the cross-compiler prefix
CC = i686-elf-gcc
AS = i686-elf-as
LD = $(CC)

# Directories
SRC_DIR = ./src
BUILD_DIR = ./output

# Output files
OUTPUT_BINARY = $(BUILD_DIR)/myos.bin
BOOT_OBJ = $(BUILD_DIR)/boot.o

# Find all C source files recursively under SRC_DIR
ALL_C_SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')
ALL_ASM_SOURCES = $(shell find $(SRC_DIR) -type f -name '*.s')
ALL_OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(ALL_C_SOURCES)) $(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/%.o,$(ALL_ASM_SOURCES))

# Compiler and linker flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS = 
LDFLAGS = -T $(SRC_DIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc

# Targets
all: $(OUTPUT_BINARY)

$(OUTPUT_BINARY): $(BOOT_OBJ) $(ALL_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

$(BOOT_OBJ): $(SRC_DIR)/boot.s
	$(AS) $(ASFLAGS) $< -o $@

# Compile each .c file found under SRC_DIR recursively to .o files in BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile each .s file found under SRC_DIR recursively to .o files in BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

# Clean target
clean:
	rm -f $(BUILD_DIR)/*.o $(OUTPUT_BINARY)

# Run qemu emulator
run:
	qemu-system-i386 -kernel $(OUTPUT_BINARY)

# PHONY target
.PHONY: all clean run
