SRC_DIR     := ./src
BUILD_DIR   := ./build
BIN			:= ./bin
LIMINE_BIN  := $(BIN)/limine
ISO_DIR     := $(BUILD_DIR)/iso

OVMF := $(BIN)/OVMF_CODE.4m.fd

KERNEL      := $(BUILD_DIR)/luna.elf
ISO         := $(BUILD_DIR)/luna.iso

CC          := x86_64-elf-gcc
LD          := x86_64-elf-ld

CFLAGS      := -Wall -Wextra -std=c11 -ffreestanding -fno-stack-protector \
               -fno-stack-check -fno-lto -fno-pie -fno-pic -m64 -march=x86-64 \
               -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone \
               -I$(SRC_DIR) -Ilimine-protocol

LDFLAGS     := -T linker.ld -static -nostdlib -no-pie -z max-page-size=0x1000

SRCS        := $(shell find $(SRC_DIR) -name '*.c')
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean run

all: $(ISO)

$(ISO): $(KERNEL) limine.conf
	@mkdir -p $(ISO_DIR)/EFI/BOOT
	cp $(KERNEL) limine.conf \
	   $(LIMINE_BIN)/limine-bios.sys \
	   $(LIMINE_BIN)/limine-bios-cd.bin \
	   $(LIMINE_BIN)/limine-uefi-cd.bin $(ISO_DIR)/
	cp $(LIMINE_BIN)/BOOTX64.EFI $(ISO_DIR)/EFI/BOOT/
	xorriso -as mkisofs -b limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		$(ISO_DIR) -o $(ISO)
	limine bios-install $(ISO)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

run: $(ISO)
	qemu-system-x86_64 -pflash $(OVMF) -cdrom $(ISO) -m 512M -serial stdio

clean:
	rm -rf $(BUILD_DIR)