CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++2a -g -fstandalone-debug

tests: bin/tests


bin/tests: ./tests/tests.cpp  ./src/FlyNetwork.cpp ./src/utils.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

.DEFAULT_GOAL := tests
.PHONY: clean tests

clean:
	rm -fr bin/* obj/*