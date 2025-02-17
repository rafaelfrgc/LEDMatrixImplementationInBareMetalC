GDB     = gdb-multiarch
CC      = arm-none-eabi-gcc
AS	    = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy # Used to convert .raw into .o
ASFLAGS = -g
CFLAGS  = -g -O1 -ffreestanding -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
          -ICMSIS/Device/ST/STM32L4xx/Include -ICMSIS/Include
LDFLAGS = -nostdlib -T ld_ram.lds

# Automatically find all .c and .s source files in the current directory
SRCS_C 	 = $(wildcard *.c)
SRCS_S	 = $(wildcard *.s)
SRCS_RAW = $(wildcard *.raw)

# Derive object files from source files
OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.s=.o)
OBJS_RAW = $(SRCS_RAW:.raw=.o)
OBJS   = $(OBJS_C) $(OBJS_S) $(OBJS_RAW) clocks.o

TARGET = main.elf

all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# Rule to convert .raw files to .o files
%.o: %.raw
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm $< $@

# Start the JLinkGDB debug server
connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

# Launch the debugger with the executable
debug: $(TARGET)
	$(GDB) -x se203.gdb $(TARGET)

# Enable UART
uart:
	JLinkExe -device STM32L475VG -if SWD -autoconnect 1 -speed auto

clean:
	rm -f $(filter-out clocks.o, $(OBJS)) $(TARGET)

.PHONY: all connect debug clean
