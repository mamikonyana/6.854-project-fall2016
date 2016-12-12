# Compiler
CC = g++
CCFLAGS=-std=c++11

# Project folders
BUILD_DIR = build
PROJECT_SRC = src
TEST_DIR = test

default: clean ${BUILD_DIR}/main

test_files = $(wildcard ${TEST_DIR}/test_*.cpp)
all_cpp_files = $(wildcard ${PROJECT_SRC}/*.cpp)
cpp_files = $(filter-out ${PROJECT_SRC}/main.cpp, $(all_cpp_files))

clean:
	rm -f ${BUILD_DIR}/main
	rm bench/*.exe bench/*.txt bench/*.csv
.PHONY: clean

plots/compare_monotonicity.png: bench/compare_monotonicity.csv
	cat $^

bench/compare_monotonicity.csv: bench/compare_monotonicity.exe data/10k_gon-0.55.csv data/10k_random_walk_2d-0.02.csv
	./$^

plots/monotonicity_10k_gon-0.55.png: bench/bce_monotonicity_10k_gon-0.55.txt
	mkdir -p plots
	python vis/answer_triangle.py bench/bce_monotonicity_10k_gon-0.55.txt --png plots/monotonicity_10k_gon-0.55.png
	open plots/monotonicity_10k_gon-0.55.png

plots/diameter_random_walk_0.02.png: bench/naive_diameter_random_walk-0.02.txt
	mkdir -p plots
	python vis/answer_triangle.py bench/naive_diameter_random_walk-0.02.txt --png plots/diameter_random_walk_0.02.png
	open plots/diameter_random_walk_0.02.png

bench/bce_monotonicity_10k_gon-0.55.txt: data/10k_gon-0.55.csv bench/bce_monotonicity.exe
	./bench/bce_monotonicity.exe data/10k_gon-0.55.csv bench/bce_monotonicity_10k_gon-0.55.txt

bench/naive_diameter_random_walk-0.02.txt: data/10k_random_walk_2d-0.02.csv bench/naive_diameter.exe
	./bench/naive_diameter.exe data/10k_random_walk_2d-0.02.csv bench/naive_diameter_random_walk-0.02.txt

data/10k_gon-0.55.csv:
	python datagen/regular_ngon.py --radius 0.55 --n 10000 -o data/10k_gon-0.55.csv

data/10k_random_walk_2d-0.02.csv:
	python datagen/random_walk_2d.py -o data/10k_random_walk_2d-0.02.csv --step-size 0.02

%.exe:
	${CC} ${CCFLAGS} -o $@ $*.cpp ${cpp_files}

DATA=data/10k_random_walk_2d.csv

naive: bench/naive_diameter.exe ${DATA}
	@echo Build Successful! Running...
	@echo
	./bench/naive_diameter.exe ${DATA} bench/naive_diameter.txt
	head bench/naive_diameter.txt
.PHONY: rebuildrun

N = 2000 # If i put this as a target specific variable, variable substitution fails...
rebuildrun: clean ${BUILD_DIR}/main data/gaussian_$(N).csv
	@echo Build Successful! Running...
	@echo
	./${BUILD_DIR}/main data/gaussian_$(N).csv
.PHONY: rebuildrun

data/gaussian_%.csv:
	python datagen/moving_gaussian.py --num-points $* -o data/gaussian_$*.csv --speed 1 --covariance 0.2 0 0 1

data/10k_random_walk_2d.csv:
	python datagen/random_walk_2d.py -o data/10k_random_walk_2d.csv --step-size 0.02

build/main:
	${CC} ${CCFLAGS} -o ${BUILD_DIR}/main src/main.cpp ${cpp_files}


test:
	@echo test files ${test_files}
	@rm -f ${TEST_DIR}/tmp
	for testfile in ${test_files} ; do \
		echo "==== running $$testfile .." ; \
		${CC} ${CCFLAGS} -I${PROJECT_SRC}/ -o ${TEST_DIR}/tmp $$testfile ${cpp_files} ; \
		./${TEST_DIR}/tmp ; \
	done
.PHONY: test

testcurrent: FILE=test/test_polyarc.cpp
testcurrent:
	@echo ==== running ${FILE}
	${CC} ${CCFLAGS} -I${PROJECT_SRC}/ -o ${TEST_DIR}/tmp ${FILE} ${cpp_files}
	./${TEST_DIR}/tmp 

