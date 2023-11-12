#include <iostream>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>

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

void printGraph(Graph game)
{
    for(uint i = 0; i < (*game).size(); ++i){
        for(auto j = (*game)[i].begin(); j != (*game)[i].end(); ++j){
            std::cout << i;
            std::cout << *j;
        }
    }
}

void printLevel(int* level, std::size_t size)
{
    for(std::size_t i = 0; i < size; ++i){
        std::cout << i << "->" << level[i] << std::endl;
    }
}

void findLeafs(std::list<int>& leafs, Graph game)
{
    for(uint i = 0; i < game->size(); ++i){
        if((*game)[i].size() == 1 && (*game)[i].front().state == false)
            leafs.push_back((*game)[i].front().index);
    }
}

bool levelGraphConstruction(int* level, Graph game, int source, int sink)
{
    for(uint i = 0; i < game->size(); ++i) 
        level[i] = -1;
    level[source] = 0;
    std::queue<int> todo;
    todo.push(source);

    while(!todo.empty()){
        int current = todo.front();
        todo.pop();
        for(auto i = (*game)[current].begin(); i != (*game)[current].end(); ++i){
            if(level[i->destination] < 0 && i->flow < i->weight){
                todo.push(i->destination);
                level[i->destination] = level[current]+1;
            }
        }
    }

    return level[sink] > -1;
}

int pushFlow(int source, int sink, int flow, Graph game, int* level)
{
    if(source == sink) return flow;
    for(auto i = (*game)[source].begin(); i != (*game)[source].end(); ++i){
        if(level[i->destination] == level[source] + 1 && i->flow < i->weight){
            int currentFlow = std::min(flow, i->weight - i->flow);
            int recurseFlow = pushFlow(i->destination, sink, currentFlow, game, level);
            if(recurseFlow > 0){
                i->flow += recurseFlow;
                return recurseFlow;
            }
        }
    }
    return 0;
}

int maxflow(Graph game, int source, int sink)
{
    if(source == sink) return -1;
    int answer = 0;
    int level[game->size()];
    
    while(levelGraphConstruction(level, game, source, sink)){
        for(int flow = pushFlow(source, sink, INT32_MAX, game, level); flow != 0; flow = pushFlow(source, sink, flow, game, level))
            answer += flow;
    }

    return answer;
}

int shield()
{
    Graph game = constructGraph();
    int solution = 0;
    std::list<int> leafs;
    findLeafs(leafs, game);
    if(!leafs.empty())
        solution  = leafs.front();
    else
        solution = maxflow(game, 0, 3);

    delete game;
    return solution;
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
    return 0;
}