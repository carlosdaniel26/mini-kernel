CC = i686-elf-gcc
AS = nasm
LD = $(CC)
ARCH = i686

SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDE_DIR = ./include

OUTPUT_BINARY = $(BUILD_DIR)/myos.bin
BOOT_OBJ = $(BUILD_DIR)/boot.o

# Compiler and linker flags
CFLAGS = -g -std=gnu99 -ffreestanding -Wall -Wextra -I$(INCLUDE_DIR) -D$(ARCH)
ASFLAGS = -felf32
LDFLAGS = -T $(SRC_DIR)/linker/linker.ld -ffreestanding -O2 -nostdlib

# Find ALL C, ASM sources
ALL_C_SOURCES := $(shell find $(SRC_DIR) $(INCLUDE_DIR) -type f -name '*.c')
ALL_ASM_SOURCES := $(shell find $(SRC_DIR) -type f -name '*.s')

# Get the DIR list from all the SOURCES
ALL_C_DIRS := $(sort $(dir $(ALL_C_SOURCES)))
ALL_ASM_DIRS := $(sort $(dir $(ALL_ASM_SOURCES)))

# Get All the OBJ target path based on the sources
ALL_OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, \
				$(filter-out $(INCLUDE_DIR)/%, $(ALL_C_SOURCES))) \
			$(patsubst $(INCLUDE_DIR)/%.c, $(BUILD_DIR)/%.o, \
				$(filter $(INCLUDE_DIR)/%, $(ALL_C_SOURCES))) \
			$(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.o, \
				$(ALL_ASM_SOURCES))

# Main target
all: build $(OUTPUT_BINARY)

# linking all object files into the final binary output
$(OUTPUT_BINARY): $(BOOT_OBJ) $(ALL_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

$(BOOT_OBJ): $(SRC_DIR)/boot.s
	$(AS) $(ASFLAGS) $< -o $@

# Rule for assembling the boot assembly file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile each .c(C file) found on INCLUDE_DIR recursively to .Os in BUILD_DIR
$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile each .s(ASM) found on SRC_DIR recursively to each file .o in BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

# Create the build DIR and SUBDIRs
build:
	mkdir -p $(BUILD_DIR)
	@for dir in $(ALL_C_DIRS); do mkdir -p $(BUILD_DIR)/$$dir; done
	@for dir in $(ALL_ASM_DIRS); do mkdir -p $(BUILD_DIR)/$$dir; done

# Clean build dir
clean:
	rm -rf $(BUILD_DIR)

dev:
	$(MAKE) clean
	$(MAKE)
	$(MAKE) run
debug:
	$(MAKE) clean
	$(MAKE)
	$(MAKE) run-debug

# Alvo para executar o emulador QEMU
run-debug:
	qemu-system-i386 -kernel $(OUTPUT_BINARY) -no-reboot
run:
	qemu-system-i386 -kernel $(OUTPUT_BINARY)

# Alvo PHONY
.PHONY: all clean run build
