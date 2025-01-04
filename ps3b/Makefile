CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
BOOST_LIBS = -lboost_unit_test_framework

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
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(BOOST_LIBS)

run_test: test
	./test

lint:
	cpplint --filter=-legal/copyright *.cpp *.hpp

clean:
	rm -f *.o NBody NBody.a test

.PHONY: all clean lint run_test