compileTestReport: modprim7.cpp edge.h unitTests.cpp
	g++ -g -std=gnu++17 -Wall -Wextra -Werror -Wshadow -Wconversion -fprofile-arcs -ftest-coverage -fPIC -O0 -c modprim7.cpp
	g++ -g -std=gnu++17 -Wall -Wextra -Werror -Wshadow -Wconversion -fprofile-arcs -ftest-coverage -fPIC -O0 -c unitTests.cpp
	g++ -fprofile-arcs -ftest-coverage -fPIC -O0 modprim7.o unitTests.o -o test
	./test < input.txt
	gcovr --html-details -o report.html
	firefox report.html && valgrind --log-file="ValgrindReport.txt" ./test < input.txt

clean:
	rm -f test
	rm -f report.css
	find . -type f -name '*.gcda' -delete
	find . -type f -name '*.gcno' -delete
	find . -type f -name '*.html' -delete
	rm -f unitTests.o && rm -f modprim7.o
	rm -f ValgrindReport.txt
	clear