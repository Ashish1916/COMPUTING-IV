CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -pedantic -g
SFML_LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system


SRCS = Sokoban.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)


HDRS = Sokoban.hpp

all: Sokoban Sokoban.a

Sokoban: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

Sokoban.a: Sokoban.o
	ar rcs $@ $^

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

lint:
	cpplint --filter=-legal/copyright *.cpp *.hpp

clean:
	rm -f *.o Sokoban Sokoban.a

.PHONY: all lint clean