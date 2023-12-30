NAME := eta_test
EXEC := bin/$(NAME)
CXX  := clang
CXXFLAGS :=
FILES := source/generator/compiler.cpp source/tester.cpp source/generator/native_writer.cpp


all: build

build:
	$(CXX) $(FILES) $(CXXFLAGS) -o $(EXEC)

run:
	$(EXEC)
