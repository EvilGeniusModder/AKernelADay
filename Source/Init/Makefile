# Tell the system what program name we are going to compile to.
TARGET=init

# Ask the shell to gather up all c files for us, then add to list.
CSOURCES = ${shell echo *.c}
SSOURCES = ${shell echo *.s}
OBJECTS = ${CSOURCES:%.c=Build/%_c.o}
OBJECTS += ${SSOURCES:%.s=Build/%_s.o}


# Tell base.mk we will need the ctr0 object file to be linked in.
__CRT0__ := true

# Linker flags, not used yet since we are not really implementing anything.
LDFLAGS = # -L${OS_PATH}/lib -lcore

all: create_directory ${TARGET}

${TARGET}: ${OBJECTS}
	${CC} ${FLAGS} -o ${TARGET} ${OBJECTS} ${LDFLAGS}

.PHONY: all

include ../../base.mk