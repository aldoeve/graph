#include <iostream>
#include <string.h>
#include <vector>
#include <list>

struct Edge{
    int destination, weight, reverse;
    bool state;
    int index, flow = 0;
    Edge(int d, int w, int r, bool s, int i): 
        destination(d), weight(w), reverse(r), state(s), index(i){;} 
};
using Graph = std::vector<std::list<Edge>>*;

Graph constructGraph(unsigned long int& map)
{
    int source, destination, weight;
    int numOfState, size;
    unsigned long int math = 1;
    unsigned long int seen = 0;

    std::cin >> size;
    Graph game = new std::vector<std::list<Edge>>;
    game->resize(size);

    for(int i = 0; i < 2; ++i){
        std::cin >> numOfState;
        for(int j = 0; j < numOfState; ++j){
            std::cin >> source >> destination >> weight;
            --source; --destination;
        
            if((map & (math << source)) > 0) seen =  seen | (math << source);
            if((map & (math << destination)) > 0) seen = seen | (math << destination);
            if(!i) seen = seen | (math << source) | (math << destination);
            map = map | (math << source) | (math << destination);
            

            if(!i) weight = 111;
            Edge temp(destination, weight, source, !i, j);
            Edge temp2(source, weight, destination, !i, j);
            (*game)[source].push_back(temp);
            (*game)[destination].push_back(temp2);
        }
    }
    map = map xor seen;
    return game;
}

int leafSelection(unsigned long int leafs, Graph game)
{
    unsigned int count = 0;
    while(leafs > 0){
        ++count;
        leafs = leafs >> 1;
    }
    return (*game)[--count].front().index;
}

int sheild()
{
    unsigned long map = 0;
    Graph game = constructGraph(map);
    if(map > 0) return leafSelection(map, game);


    return 0;
}

int cut()
{
    unsigned long int map = 0;
    Graph game = constructGraph(map);
    if(map > 0) return leafSelection(map, game);
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc != 2) return 0;
    int choosenEdge = strcmp(argv[1], "short\n") ? sheild():cut();
    std::cout << choosenEdge << std::endl;
    return 0;
}