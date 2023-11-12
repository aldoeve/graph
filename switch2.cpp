#include <iostream>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <list>

struct Edge{
    int destination, weight;
    const bool state;
    int index, flow = 0;
    Edge(int d, int w, bool s, int i): destination(d), weight(w), state(s), index(i){;}
};

std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
    return os << edge.destination << edge.weight << std::endl;
}

using Graph = std::vector<std::list<Edge>>*;

Graph constructGraph()
{
    int source, destination, weight;
    int numOfState, maxsize;
    
    std::cin >> maxsize;
    Graph game = new std::vector<std::list<Edge>>;
    game->resize(maxsize);
    
    for(int i = 0; i < 2; ++i){
        std::cin >> numOfState;
        bool state = i == 0 ? true : false;
        for(int j = 0; j < numOfState; ++j){
            std::cin >> source >> destination >> weight;
            Edge temp(destination, weight, state, j);
            Edge temp2(source, weight, state, j);
            (*game)[source].push_back(temp);
            (*game)[destination].push_back(temp2);
        }
    }
    
    return game;
}

int shield()
{
    Graph game = constructGraph();
    delete game;
    return INT32_MIN;
}

int cut()
{
    return INT32_MIN;
}


int main(int argc, char* argv[])
{
    if(argc != 2){std::cout << "ERROR: missing input\n"; return 0;}
    int modifiedEdge = strcmp(argv[1], "short\n") ? shield() : cut();
    std::cout << modifiedEdge << std::endl;
}