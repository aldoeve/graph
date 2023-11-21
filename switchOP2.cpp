#include <iostream>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <chrono>

struct Edge{
    int destination, weight;
    bool state;
    int index, flow = 0;
    Edge(int d, int w, bool s, int i): destination(d), weight(w), state(s), index(i){;}
};

std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
    return os << ',' <<edge.destination << '=' << edge.weight << std::endl;
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
        for(int j = 0; j < numOfState; ++j){
            std::cin >> source >> destination >> weight;
            --source; --destination;
            if(!i) weight = INT32_MAX;
            Edge temp(destination, weight, !i, j);
            Edge temp2(source, weight, !i, j);
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
            std::cout << *j << '=';
            std::cout << j->flow << std::endl;
        }
    }
}

void printLevel(int* level, std::size_t size)
{
    for(std::size_t i = 0; i < size; ++i){
        std::cout << i << "->" << level[i] << std::endl;
    }
}

int findLeaf(Graph game)
{
    for(uint i = 0; i < game->size(); ++i){
        if((*game)[i].size() == 1 && (*game)[i].front().state == false)
            return (*game)[i].front().index;
    }
    return -1;
}

bool levelGraphConstruction(int* level, Graph game, const int source, const int sink)
{
    for(uint i = 0; i < game->size(); ++i) 
        level[i] = -1;
    level[source] = 0;
    std::queue<int> todo;
    todo.push(source);
    int current;

    while(!todo.empty()){
        current = todo.front();
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

int pushFlow(const int source, const int sink, int flow, Graph game, int* level)
{
    int currentFlow, recurseFlow;
    if(source == sink) return flow;
    for(auto i = (*game)[source].begin(); i != (*game)[source].end(); ++i){
        if(level[i->destination] == level[source] + 1 && i->flow < i->weight){
            currentFlow = std::min(flow, i->weight - i->flow);
            recurseFlow = pushFlow(i->destination, sink, currentFlow, game, level);
            if(recurseFlow > 0){
                i->flow += recurseFlow;
                for(auto j = (*game)[i->destination].begin(); j != (*game)[i->destination].end(); ++j){
                    if(j->destination == source){
                        j->flow -= recurseFlow;
                        return recurseFlow;
                    }
                }
                return recurseFlow;
            }
        }
    }
    return 0;
}

std::list<int> maxflow(Graph game, const int source, const int sink)
{
    std::list<int> cutset;
    if(source == sink) return cutset;
    int level[game->size()];
    
    while(levelGraphConstruction(level, game, source, sink)){
        for(int flow = pushFlow(source, sink, INT32_MAX, game, level); flow != 0; flow = pushFlow(source, sink, flow, game, level))
            ;
    }

    int smallestWeight = INT32_MAX;
    for(uint i = 0; i < (*game).size(); ++i){
        for(auto j = (*game)[i].begin(); j != (*game)[i].end(); ++j){
            if(j->weight - j->flow == 0 && j->state == false){
                if(smallestWeight > j->weight){
                    cutset.push_front(j->index);
                    smallestWeight = j->weight;
                }
                else
                    cutset.push_back(j->index);
            }
        }
    } 
    return cutset;
}

int shield()
{
    Graph original = constructGraph();
    std::vector<std::list<Edge>> temp = *original;
    Graph game = &temp;
    int solution = 0;
    int leaf = findLeaf(game);
    if(leaf > -1)
        solution  = leaf;
    else{
        std::list<int> cutset;
        int smallestSeen = INT32_MAX;
        int size = (int)(game->size());
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                std::list<int> check = maxflow(game, i, j);
                if((int)(check.size()) < smallestSeen && check.size() != 0)
                    cutset = check;
                temp = *original;
            }
        }
        if(smallestSeen < INT32_MAX)
            solution = cutset.front();
    }
    delete original;
    return solution;
}

int cut()
{
    Graph original = constructGraph();
    std::vector<std::list<Edge>> temp = *original;
    Graph game = &temp;
    int solution = 0;
    int leaf = findLeaf(game);
    if(leaf > -1)
        solution  = leaf;
    else{
        std::list<int> cutset;
        int smallestSeen = INT32_MAX;
        int size = (int)(game->size());
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                std::list<int> check = maxflow(game, i, j);
                if((int)(check.size()) < smallestSeen && check.size() != 0)
                    cutset = check;
                temp = *original;
            }
        }
        if(smallestSeen < INT32_MAX)
            solution = cutset.front();
    }
    delete original;
    return solution;
}

int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    if(argc != 2){std::cout << "ERROR: missing input\n"; return 0;}
    int modifiedEdge = strcmp(argv[1], "short\n") ? shield() : cut();
    std::cout << modifiedEdge << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << duration.count() << std::endl;
    return 0;
}
//0.0000772732
//0.0000806331
//0.0000800818
//0.0000788304
//0.0000803374
//0.0000798422