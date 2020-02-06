CXX      := -c++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -std=c++11
LDFLAGS  := -g

all: triangulate_test

triangulate.o: triangulate.cpp triangulate.h
	$(CXX) $(CXXFLAGS) -c triangulate.cpp -o triangulate.o

test.o: test.cpp triangulate.h
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

triangulate_test: test.o triangulate.o
	$(CXX) $(LDFLAGS) triangulate.o test.o -o triangulate_test

test: triangulate_test
	./triangulate_test

.PHONY: clean
clean:
	-@rm -rvf *.o
	-@rm -rvf triangulate_test
