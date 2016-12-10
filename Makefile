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

N = 2000

rebuildrun: clean ${BUILD_DIR}/main data/gaussian_$(N).csv
	@echo Build Successful! Running...
	@echo
	./${BUILD_DIR}/main data/gaussian_$(N).csv
.PHONY: rebuildrun

data/gaussian_%.csv:
	python datagen/moving_gaussian.py --num-points $* -o data/gaussian_$*.csv --speed 1 --covariance 0.03 0 0 1

build/main:
	${CC} ${CCFLAGS} -o ${BUILD_DIR}/main src/main.cpp src/helpers.cpp src/naive.cpp

test: TEST=naive
test:
	@rm -f ${TEST_DIR}/tmp
	${CC} ${CCFLAGS} -I${PROJECT_SRC}/ -o ${TEST_DIR}/tmp ${TEST_DIR}/test_${TEST}.cpp ${PROJECT_SRC}/naive.cpp ${PROJECT_SRC}/helpers.cpp
	./${TEST_DIR}/tmp
.PHONY: test

