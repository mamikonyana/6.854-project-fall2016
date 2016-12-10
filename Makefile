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
	python datagen/moving_gaussian.py --num-points $* -o data/gaussian_$*.csv --speed 1 --covariance 0.2 0 0 1

build/main:
	${CC} ${CCFLAGS} -o ${BUILD_DIR}/main src/main.cpp src/helpers.cpp src/naive.cpp src/bce.cpp

test_files = $(wildcard ${TEST_DIR}/test_*.cpp)

test:
	@echo test files ${test_files}
	@rm -f ${TEST_DIR}/tmp
	for testfile in ${test_files} ; do \
		echo "==== running $$testfile .." ; \
		${CC} ${CCFLAGS} -I${PROJECT_SRC}/ -o ${TEST_DIR}/tmp $$testfile ${PROJECT_SRC}/naive.cpp ${PROJECT_SRC}/helpers.cpp ${PROJECT_SRC}/bce.cpp ; \
		./${TEST_DIR}/tmp ; \
	done
.PHONY: test

