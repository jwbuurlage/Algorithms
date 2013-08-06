all: solution

solution: solution.cpp
	g++ -O3 -o solution solution.cpp

test: solution
	./solution < sample.in > solution.out
	vimdiff solution.out sample.out
