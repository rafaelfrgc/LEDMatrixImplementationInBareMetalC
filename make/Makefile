CC             =  arm-none-eabi-gcc
CFLAGS         = -Wall -Werror -g -Og -mthumb
CFLAGS_STUBS   = -g -O2 -mthumb
LDFLAGS        = -L/opt/mylibs -mthumb
LIBS           = -lm

# Source and object files
SRC     = $(wildcard *.c)
OBJS     = $(SRC:.c=.o)
HEADERS = $(wildcard *.h)

TARGET = hello

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJS) stubs.o
	$(CC) $(LDFLAGS) $(OBJS) stubs.o $(LIBS) -o $(TARGET)

# Compile stubs.o
stubs.o: libs/stubs.c
	$(CC) $(CFLAGS_STUBS) -c -o $@ $<

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
