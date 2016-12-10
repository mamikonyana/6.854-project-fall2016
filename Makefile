# Compiler
CC = gcc

# Project folders
BUILD_DIR = build
PROJECT_SRC = src
TEST_DIR = test

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
	${CC} -o ${BUILD_DIR}/main src/main.c src/bce.c src/naive.c src/helpers.c

test:
	@rm -f ${TEST_DIR}/tmp
	${CC} -I ${PROJECT_SRC}/* -o ${TEST_DIR}/tmp ${TEST_DIR}/test_helpers.c
	./${TEST_DIR}/tmp
.PHONY: test
