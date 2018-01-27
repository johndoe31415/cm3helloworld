.PHONY: all clean readflash program bindump gdb gdbserver console tests readflash ocdconsole
.SUFFIXES: .txt

TARGETS := helloworld helloworld.bin

PREFIX := arm-none-eabi-
CC := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump
AR := $(PREFIX)ar
GDB := $(PREFIX)gdb
OPENOCD := /home/joe/bin/gcc/openocd/bin/openocd
OPENOCD_SCRIPT_DIR := /home/joe/bin/gcc/openocd/share/openocd/scripts/
BUILD_TIMESTAMP_UTC := $(shell /bin/date +'%Y-%m-%d %H:%M:%S')
#BUILD_REVISION := $(shell git describe --abbrev=10 --dirty --always)

CFLAGS := $(CFLAGS) -std=c11
CFLAGS += -Wall -Wmissing-prototypes -Wstrict-prototypes -Werror=implicit-function-declaration -Werror=format -Wimplicit-fallthrough -Wshadow
CFLAGS += -Os -g3
CFLAGS += -mcpu=cortex-m3 -mthumb
CFLAGS += -include library_config.h -Iext-st/include -Iext-st/include-cmsis -Iext-st/include-cmsis-dev
CFLAGS += -DBUILD_TIMESTAMP_UTC='"$(BUILD_TIMESTAMP_UTC)"' -DBUILD_REVISION='"$(BUILD_REVISION)"'
CFLAGS += -ffunction-sections -fdata-sections
#CFLAGS += -specs=nano.specs -specs=rdimon.specs
LDFLAGS := -Tstm32f101c8t6.ld
WRITE_ADDR := 0x08000000
LDFLAGS += -Wl,--gc-sections
STATICLIBS := ext-st/stdperiph.a

OBJS := main.o ivt.o init.o pinmap.o
ADDITIONAL_DEPENDENCY := pinmap.h

all: $(TARGETS)

tests:
	make -C tests all test

clean:
	rm -f $(OBJS) $(TARGETS)
	rm -f helloworld.sym
	rm -f read_flash.bin

gdb:
	$(GDB) -d ext-st helloworld -ex "target extended-remote :3333"

openocd:
	$(OPENOCD) -s $(OPENOCD_SCRIPT_DIR) -f interface/jlink.cfg -c "adapter_khz 1000" -c "transport select swd" -f target/stm32f1x.cfg

reset:
	echo "halt; reset" | nc -N 127.0.0.1 4444

ocdconsole:
	telnet 127.0.0.1 4444

program: helloworld.bin
	echo "halt; flash write_image erase unlock helloworld.bin $(WRITE_ADDR); reset" | nc -N 127.0.0.1 4444

readflash:
	echo "halt; dump_image read_flash.bin $(WRITE_ADDR) 0x10000; reset " | nc -N 127.0.0.1 4444

console:
	picocom --baud 115200 /dev/ttyUSB*

bindump: helloworld.bin
	$(OBJDUMP) -b binary -m armv3m -D $<

helloworld: $(ADDITIONAL_DEPENDENCY) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(STATICLIBS)

helloworld.bin: helloworld
	$(OBJCOPY) -O binary $< $@

helloworld.sym: helloworld.c
	$(CC) $(CFLAGS) -E -dM -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.s.o:
	$(CC) $(CFLAGS) -c -o $@ $<

pinmap.h: pinmap.txt
	./genpinmap.py
