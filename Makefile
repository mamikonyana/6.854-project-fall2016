# Compiler
CC = g++
CCFLAGS=-std=c++11

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
.PHONY: rebuildrun

build/main:
	${CC} ${CCFLAGS} -o ${BUILD_DIR}/main src/main.cpp src/helpers.cpp src/naive.cpp

test:
	@rm -f ${TEST_DIR}/tmp
	${CC} ${CCFLAGS} -I ${PROJECT_SRC}/* -o ${TEST_DIR}/tmp ${TEST_DIR}/test_helpers.c
	./${TEST_DIR}/tmp
.PHONY: test

