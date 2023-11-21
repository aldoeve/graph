SHELL := bash
compile&run: switchOP2.cpp
	g++ -g -std=gnu++17 -Wall -Wextra -Werror -Wshadow -Wconversion switchOP2.cpp -o test 
	./test short < test.txt

loop:
	for i in {1..100}; do ./test short < test.txt >> output.txt; done

memcheck:
	valgrind ./test short < test.txt

play:
	./test short < test.txt


clean:
	rm -f test
	rm -f output.txt
	clear