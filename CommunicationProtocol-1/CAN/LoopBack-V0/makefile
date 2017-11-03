ifeq (${CC},picc18)
CC := picc18
INCLUDE_PATH := /usr/hitech/picc-18/std/9.52/include/
COMPILER = 2
else
ifeq (${CC},xc8)
CC := xc8
INCLUDE_PATH := /opt/microchip/xc8/v1.36/include/
COMPILER = 1
else
$(error "Compiler not defined!!. Use CC=<compiler name>")
endif
endif

CHIP := 18F4580
FLASH_REGION := 0-3000 

ifeq (${SRCS},)
SRCS := $(wildcard *.c)
endif
ifeq (${INCS},)
INCS := $(wildcard *.h)
endif
ifeq (${OBJS},)
OBJS := $(SRCS:.c=.obj)
endif
ifeq (${P1},)
OBJS := $(SRCS:.c=.p1)
endif
TARGET := pic${CHIP}

AR := libr
#PROG := tinybldlin
PROG := ~/SVN/Development/Software/Microcontrollers/PIC/DevelopmentBoards/RhydoLabz-eCeePIC18F4580/Tools/tinybldlin/src/tinybldlin.py
PORT := /dev/ttyUSB0

MIN_CFLAGS := --chip=${CHIP} -I${INCLUDE_PATH} --ROM=${FLASH_REGION}
# The following MSG_CFLAGS controls the compiler messages
MSG_CFLAGS := -Q
# The following OPT_CFLAGS reduces the code size
OPT_CFLAGS := --opt=all
# The following OUT_CFLAGS controls the generated outputs
OUT_CFLAGS := --asmlist --summary=psect,mem -M${TARGET}.map 
EXTRA_CFLAGS += ${MSG_CFLAGS} ${OPT_CFLAGS} ${OUT_CFLAGS}
CFLAGS := ${MIN_CFLAGS} ${EXTRA_CFLAGS} -DCOMPILER=${COMPILER}
ARFLAGS := r

${TARGET}.hex: ${OBJS}
	${CC} ${CFLAGS} -intel $^ -o$@
	${MAKE} xclean

${TARGET}.bin: ${OBJS}
	${CC} ${CFLAGS} -bin $^ -o$@
	${MAKE} xclean

%.p1: %.c ${INCS}
	${CC} ${CPPFLAGS} ${CFLAGS} --pass1 $<

%.obj: %.c ${INCS}
	${CC} ${CPPFLAGS} ${CFLAGS} -C $<

%.as: %.c ${INCS}
	${CC} ${CPPFLAGS} ${CFLAGS} -S $<

%.lib: %.obj
	${AR} ${ARFLAGS} $@ $<

xclean:
	rm -f *.rlf
clean: xclean 
	rm -f *.rlf ${OBJS}

allclean: xclean
	rm -f $(filter-out ${SRCS} ${INCS}, $(wildcard *.*)) funclist

package: makefile ${SRCS} ${INCS} ${TARGET}.*
	tar -zcvf project.tgz $^

burn: ${TARGET}.hex 
	${PROG} --port ${PORT} --file $^ 
