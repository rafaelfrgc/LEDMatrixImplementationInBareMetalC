GDB     = arm-none-eabi-gdb
CC      = arm-none-eabi-gcc
AS	    = arm-none-eabi-as
ASFLAGS = -g
CFLAGS  = -g -O1 -ffreestanding -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS = -nostdlib -T ld_ram.lds

# Automatically find all .c and .s source files in the current directory
SRCS_C = $(wildcard *.c)
SRCS_S = $(wildcard *.s)

# Derive object files from source files
OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.s=.o)
OBJS = $(OBJS_C) $(OBJS_S) clocks.o

TARGET = main.elf

all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# Start the debug server
connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

# Launch the debugger with the executable
debug: $(TARGET)
	$(GDB) -x se203.gdb $(TARGET)

clean:
	rm -f $(filter-out clocks.o, $(OBJS)) $(TARGET)

.PHONY: all clean connect debug
