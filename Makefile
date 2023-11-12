compile&run: switch2.cpp
	g++ -g -std=gnu++17 -Wall -Wextra -Werror -Wshadow -Wconversion switch2.cpp -o test 
	./test short < test.txt

memcheck:
	valgrind ./test short < test.txt

clean:
	rm -f test
	clear