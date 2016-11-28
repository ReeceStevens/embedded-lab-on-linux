PROJ_NAME = blinky

# Compile Options

PART=TM4C123GH6PM

TIVAWARE_ROOT = ../TivaWare
TIVA_DRIVERS = $(TIVAWARE_ROOT)/driverlib

SRCS = $(wildcard *.c)
SRCS += $(TIVAWARE_ROOT)/driverlib/gcc/libdriver.a

WARNING_LEVEL = -Wall
OPTIMIZATION_LEVEL = -O0 # Required for debugging via GDB

LIBS = '$(shell $(CC) $(CFLAGS) -print-file-name=libm.a)'
LIBS += '$(shell $(CC) $(CFLAGS) -print-file-name=libc.a)'
LIBS += '$(shell $(CC) $(CFLAGS) -print-file-name=librdimon.a)'
LIBS += '$(shell $(CC) $(CFLAGS) -print-libgcc-file-name)'

LINK_LIBS = $(addprefix -L, $(LIBS))

# NOTE: GCC cannot compile the Keil assembly syntax (*.S files in Valvanoware)
# However, conversion between Keil and GCC syntax is very simple (and you probably won't
# have to do it). See startup.c functions with `__asm()` in them to see examples of
# functions that have been convereted from Keil syntax to GCC.
AFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MD

CFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -MD
CFLAGS +=  -std=c99 $(WARNING_LEVEL) -DPART_TM4C123GH6PM -c -specs=rdimon.specs -Wl,--gc-sections
CFLAGS += $(WARNING_LEVEL) $(OPTIMIZATION_LEVEL)
CFLAGS += -g -D DEBUG

DEFS = -DPART_TM4C123GH6PM -DTARGET_IS_TM4C123_RB1

INC_DIRS = $(addprefix -I, $(TIVAWARE_ROOT))
INC_DIRS += $(addprefix -I, $(TIVA_DRIVERS))
INC_DIRS += $(addprefix -I, $(EXTRA_INCLUDES))

LDFLAGS = -Ttm4c.ld --entry ResetISR

# Tool Definitions
# Either put these tools in your $PATH variable, or
# put the absolute path to the binaries here.
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
GDB = arm-none-eabi-gdb

LM4FLASH = lm4flash
OPENOCD = openocd

# Implicit Rule Definitions

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(INC_DIRS) $(DEFS) $(CFLAGS) -Wa,-adhln=assembly_output/$<.lst -c -o $@ $<

%.o: %.s
	$(CC) $(INC_DIRS) $(DEFS) -c -o $@ $< $(AFLAGS)

# Build Rules

all: $(PROJ_NAME).bin

clean:
	rm -rf *.o *.d *.bin *.elf assembly_output/*.lst

flash: $(PROJ_NAME).bin
	$(LM4FLASH) $<

debug: $(PROJ_NAME).elf
	$(OPENOCD) -f board/ek-tm4c123gxl.cfg &
	$(GDB) $<

OBJS = $(patsubst %.c, %.o, ${SRCS})

$(PROJ_NAME).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LINK_LIBS)
