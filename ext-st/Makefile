.PHONY: all setup clean

LIBRARY_PATH := STM32F10x_StdPeriph_Lib_V3.5.0
PREFIX := arm-none-eabi-
CFLAGS := $(CFLAGS) -std=c11 -Wall -Os -mcpu=cortex-m3 -g3
CFLAGS += -include ../library_config.h
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -I. -I$(LIBRARY_PATH)/Libraries/STM32F10x_StdPeriph_Driver/inc/ -I${LIBRARY_PATH}/Libraries/CMSIS/CM3/CoreSupport/ -I${LIBRARY_PATH}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/

LIBRARY_SRCS := $(wildcard $(LIBRARY_PATH)/Libraries/STM32F10x_StdPeriph_Driver/src/*.c)
LIBRARY_OBJS := $(LIBRARY_SRCS:.c=.o)

all: stdperiph.a

clean:
	rm -f ${LIBRARY_OBJS}
	rm -f reset.o stdperiph.a

stdperiph.a: $(LIBRARY_OBJS)
	${PREFIX}ar r $@ $(LIBRARY_OBJS)

.c.o:
	${PREFIX}gcc -c ${CFLAGS} -o $@ $<
