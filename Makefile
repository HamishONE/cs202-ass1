CXX = g++
CXXFLAGS = -Wall -g

all: zms zms_test

zms: main.cpp Zoo/*.cpp Zoo/*.hpp
	$(CXX) $(CXXFLAGS) -o zms $^

zms_test: test.cpp Zoo/*.cpp Zoo/*.hpp
	$(CXX) $(CXXFLAGS) -o zms_test $^

test: zms_test
	./zms_test

run: zms
	./zms

clean:
	rm -f zms zms_test