# Define o prefixo do compilador cruzado
CC = i686-elf-gcc
AS = i686-elf-as
LD = $(CC)

# Diretórios
SRC_DIR = ./src
BUILD_DIR = ./build

# Arquivos de saída
OUTPUT_BINARY = $(BUILD_DIR)/myos.bin
BOOT_OBJ = $(BUILD_DIR)/boot.o

# Compiler and linker flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(SRC_DIR)/include
ASFLAGS =
LDFLAGS = -T $(SRC_DIR)/linker/linker.ld -ffreestanding -O2 -nostdlib -lgcc

# Encontra todos os arquivos fonte C recursivamente em SRC_DIR
ALL_C_SOURCES := $(shell find $(SRC_DIR) -type f -name '*.c')
ALL_ASM_SOURCES := $(shell find $(SRC_DIR) -type f -name '*.s')
ALL_C_DIRS := $(sort $(dir $(ALL_C_SOURCES)))
ALL_ASM_DIRS := $(sort $(dir $(ALL_ASM_SOURCES)))
ALL_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(ALL_C_SOURCES)) $(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/%.o,$(ALL_ASM_SOURCES))

# Alvo principal
all: build $(OUTPUT_BINARY)

$(OUTPUT_BINARY): $(BOOT_OBJ) $(ALL_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

$(BOOT_OBJ): $(SRC_DIR)/boot.s
	$(AS) $(ASFLAGS) $< -o $@

# Compila cada arquivo .c encontrado sob SRC_DIR recursivamente para arquivos .o em BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compila cada arquivo .s encontrado sob SRC_DIR recursivamente para arquivos .o em BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

# Alvo para criar o diretório de saída
build:
	mkdir -p $(BUILD_DIR)
	@for dir in $(ALL_C_DIRS); do mkdir -p $(BUILD_DIR)/$$dir; done
	@for dir in $(ALL_ASM_DIRS); do mkdir -p $(BUILD_DIR)/$$dir; done

# Alvo de limpeza
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(OUTPUT_BINARY)

# Alvo para executar o emulador QEMU
run:
	qemu-system-i386 -kernel $(OUTPUT_BINARY)

# Alvo PHONY
.PHONY: all clean run build
