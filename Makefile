GTEST_ROOT = ../googletest/googletest
GTEST_MAIN = $(GTEST_ROOT)/make/gtest_main.a

CPPFLAGS = -I $(GTEST_ROOT)/include

# TreeBin uses C++ 2011.  Compile for debugging (-g) with warnings.
CXXFLAGS = -std=c++11 -g -Wall -Wextra

all:	test run_main

test:	tree_bin_test
	./tree_bin_test

tree_bin_test.o: tree_bin.h

tree_bin_test: tree_bin_test.o  $(GTEST_MAIN)
# On Linux, need -pthread after gtest_main.a to link correctly.
# On Mac, the -pthread gives a harmless warning that it's not needed.
	g++ -o $@ $^ -pthread

tree_bin_main.o: tree_bin.h

tree_bin_main: tree_bin_main.o
	g++ -o $@ $^

run_main: tree_bin_main
	./tree_bin_main
