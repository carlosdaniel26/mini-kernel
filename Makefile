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
KERNEL_OBJ = $(BUILD_DIR)/kernel.o

# Compiler and linker flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T $(SRC_DIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc

# Targets
all: $(OUTPUT_BINARY)

$(OUTPUT_BINARY): $(BOOT_OBJ) $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

$(BOOT_OBJ): $(SRC_DIR)/boot.s
	$(AS) $< -o $@

$(KERNEL_OBJ): $(SRC_DIR)/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(BUILD_DIR)/*.o $(OUTPUT_BINARY)

# Run qemu emulator
run:
	qemu-system-i386 -kernel $(OUTPUT_BINARY)

# PHONY target
.PHONY: all clean
