#include "printG.h"
#include "edge.h"

void printTrees(const std::list<std::list<Edge>*>& listToPrint)
{
    std::cout << "------------------------------------\n";
    for(auto i = listToPrint.begin(); i != listToPrint.end(); ++i){
        for(auto j = ++(**i).begin(); j != (**i).end(); ++j){
             std::cout << (*j);
        }
        std::cout << "------------------------------------\n";
    }
}

void printMatrix(const int order, int ** adjMatrix)
{
    for(int i(0) ; i < order; ++i){
        for(int j=0; j < order; ++j){
            std::cout << adjMatrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------------\n";
}