SHELL := bash
compile: game.cpp
	g++ -g -std=gnu++17 -Wall -Wextra -Werror -Wshadow -Wconversion game.cpp -o test 
	./test short < test2.txt

game:
	./test short < test2.txt

clean:
	rm -f test