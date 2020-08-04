
ARMGNU = arm-none-eabi

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The name of the output file to generate.
TARGET = kernel.img

# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
AOBJ := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))
COBJ := $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))
OBJECTS = $(AOBJ) $(COBJ)

# Rule to make everything.
all: init $(TARGET) $(LIST)

init:
	mkdir -p $(BUILD)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	$(ARMGNU)-objdump -d $(BUILD)output.elf > $(BUILD)$(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(BUILD)$(TARGET) 

# Rule to make the elf file using GCC as linker.
$(BUILD)output.elf : $(OBJECTS) $(LINKER)
	$(ARMGNU)-gcc -T $(LINKER) -nostartfiles $(AOBJ) $(COBJ) -o $(BUILD)output.elf 

# Rule to make the elf file using LD.
#$(BUILD)output.elf : $(OBJECTS) $(LINKER)
#	$(ARMGNU)-ld -T $(LINKER) $(AOBJ) $(COBJ) -Map $(BUILD)$(MAP) -o $(BUILD)output.elf 

# Rule to make the object files from ASM ones.
$(BUILD)%.o: $(SOURCE)%.s
	$(ARMGNU)-as -I $(SOURCE) -g -march=armv5te $< -o $@

# Rule to make the object files from C ones.
$(BUILD)%.o: $(SOURCE)%.c 
	$(ARMGNU)-gcc -I $(SOURCE) -g -fno-builtin -ffreestanding -march=armv5te -c $< -o $@

# run the program in emulator 
run:
	emulator -avd avd22 -no-snapshot-load -no-snapshot-save -shell -qemu -kernel ./build/kernel.img

# Debug the program using DDD as GUI for GDB debugger.
debug:
	emulator -avd avd22 -verbose -show-kernel -netfast -shell -no-snapshot-load -no-snapshot-save -qemu -s -S -kernel ./build/kernel.img &
	ddd --debugger arm-none-eabi-gdb ./build/output.elf

# Rule to clean files.
clean : 
	-rm -rf $(BUILD)
