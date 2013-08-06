all: solution

solution: solution.cpp
	g++ -O3 -o solution solution.cpp

test: solution
	./solution < in.txt > solution_out.txt
	vimdiff solution_out.txt out.txt
