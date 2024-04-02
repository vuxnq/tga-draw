CXX = gcc
CXXFLAGS = -Wall -Wextra -pedantic -g -lm
SRC_DIR = src/*.c
OUTPUT = program
VAL = valgrind -q --tool=memcheck --track-origins=no --error-exitcode=1 --track-origins=yes
ARGUMENTS = --output $(A_OUTPUT) --width $(A_WIDTH) --height $(A_HEIGHT)

A_WIDTH = 400
A_HEIGHT = 340
A_OUTPUT = output.tga

ifeq ($(OS),Windows_NT) 
		TARGET = $(OUTPUT).exe
	else
		TARGET = $(OUTPUT)
endif

all:
	$(CXX) $(SRC_DIR) -o $(TARGET) $(CXXFLAGS)

input1:
	$(CXX) $(SRC_DIR) -o $(TARGET) $(CXXFLAGS)
	./$(TARGET) $(ARGUMENTS) < inputs/input1.txt


input2: A_WIDTH = 64
input2: A_HEIGHT = 64
input2:
	$(CXX) $(SRC_DIR) -o $(TARGET) $(CXXFLAGS)
	./$(TARGET) $(ARGUMENTS) < inputs/input2.txt

rm:
	rm $(TARGET)