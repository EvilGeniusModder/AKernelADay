# Set our utility variables if not already set.
SHELL ?= /bin/sh
CC ?= gcc

OS_PATH ?= /mnt/GenericOS
DESTDIR ?= /mnt/GenericOS

INCLUDE ?= ${DESTDIR}/AKernelADay/Include
FLAGS ?= -nostdlib -I${INCLUDE}

PREFIX ?= ${DESTDIR}
BINDIR ?= ${PREFIX}/sbin

# Include our crt0.o file if necessary
ifdef __CRT0__
OBJECTS += ../crt0.o
endif

# Build either assembly or c files into object code.
Build/%_c.o: %.c
	${CC} ${FLAGS} -c $< -o $@

Build/%_s.o: %.s
	${CC} ${FLAGS} -c $< -o $@

# Build our crt0 into object code.
Source/crt0.o:
	${CC} ${FLAGS} -c Source/crt0.s -o Source/crt0.o

#Installs our program into its destination directory.
install:
	cp ${TARGET} ${BINDIR}/

# Fully cleans our our sbin and lib directories.
fullclean: 
	rm -rf ${DESTDIR}/sbin/*
	rm -rf  ${DESTDIR}/lib/*

# Builds a fresh image by cleaning then building.
fresh: clean ${TARGET}

# Cleans our local storage. 
clean:
	rm -rf Build/*.o ${TARGET}

# Creates the directories needed.
create_directory:
	mkdir -p Build
	mkdir -p ${BINDIR}

.PHONY: create_directory clean fresh fullclean install