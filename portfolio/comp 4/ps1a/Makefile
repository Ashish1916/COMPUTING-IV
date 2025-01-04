CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g 
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
OBJECTS = FibLFSR.o PhotoMagic.o
all: ps1 test PhotoMagic.a lint

lint: 
	cpplint *.cpp *.hpp

ps1: main.o $(OBJECTS)
	$(CC) main.o $(OBJECTS) -o ps1 $(LIB)
test: test.o $(OBJECTS)
	$(CC) test.o $(OBJECTS) -o test $(LIB)
main.o: main.cpp FibLFSR.hpp
	$(CC) -c main.cpp  $(CFLAGS)
FibLFSR.o: FibLFSR.cpp FibLFSR.hpp
	$(CC) -c FibLFSR.cpp $(CFLAGS)
PhotoMagic.o: PhotoMagic.cpp
	$(CC) -c PhotoMagic.cpp $(CFLAGS)
test.o: test.cpp FibLFSR.hpp
	$(CC) -c test.cpp $(CFLAGS)
PhotoMagic.a: $(OBJECTS)
	ar rcs PhotoMagic.a $(OBJECTS)
clean:
	rm -f *.o ps1 test PhotoMagic
