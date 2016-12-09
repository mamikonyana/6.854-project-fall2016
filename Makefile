# Compiler
CC = gcc

# Project folders
BUILD_DIR = build

default: clean ${BUILD_DIR}/main

clean:
	rm -f ${BUILD_DIR}/main
.PHONY: clean

rebuildrun: clean ${BUILD_DIR}/main
	@echo Build Successful! Running...
	@echo
	./${BUILD_DIR}/main
.PHONY: run

build/main:
	${CC} -o ${BUILD_DIR}/main src/main.c
