CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: NBody NBody.a test

NBody: main.o Universe.o CelestialBody.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

NBody.a: Universe.o CelestialBody.o
	ar rcs $@ $^

main.o: main.cpp Universe.hpp CelestialBody.hpp
	$(CXX) $(CXXFLAGS) -c $<

Universe.o: Universe.cpp Universe.hpp CelestialBody.hpp
	$(CXX) $(CXXFLAGS) -c $<

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CXX) $(CXXFLAGS) -c $<

test: test.cpp Universe.o CelestialBody.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

lint:
	cpplint --filter=-legal/copyright *.cpp *.hpp

clean:
	rm -f *.o NBody NBody.a test

.PHONY: all clean lint test