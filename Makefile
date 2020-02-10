CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
FILES = main.cpp ACSubStringSearch.h
NAME = solution

all: solution

solution: main.cpp ACSubStringSearch.h
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

clean: 
	rm -f *.o $(NAME)

