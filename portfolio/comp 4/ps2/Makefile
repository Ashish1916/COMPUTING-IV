CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = penta.hpp
# Your .cpp files
SOURCES = penta.cpp
# The name of your program
PROGRAM = Penta

.PHONY: all clean lint

all: $(PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

# Compile penta.cpp separately
penta.o: penta.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

# Link .o files to create the executable
$(PROGRAM): main.o penta.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp