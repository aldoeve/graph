# Spanning Tree HW

Disclaimers:
    The catch.hpp file is not mine and is an outdated version of https://github.com/catchorg/Catch2/blob/devel/README.md. I used an older version
    since all I need is a single convient header file without all the functionality of the whole libary that it is now.

Requirements:
    gcovr
    firefox(or any other browser but it would require modifiying the makefile)

Usage:
    A makefile has been provided. Running make will compile the program with the proper flags. The the test cases will be run to verify correctness. The answers to the test cases were derived by hand and by using properites of a complete graph. Once all the tests are ran, a report will be generated and displayed using firefox to demonstrate code coverage. An additional report named ValgrindReport.txt reports valgrinds findings on memory leaks. For the report please click on modprim file to see a more detailed view. The file printG.h contains debugging tools to allow the printing of spaning trees. The file edge.h holds the struct edge and an overload for easy printing of a graph for printG.h. The printing functions are not run on regular testing due to large amounts of output on some matrices.

Description:
    This program finds all spaning trees, all minimum spanning trees, and all maximum spaning trees in a given matrix representation of a graph.