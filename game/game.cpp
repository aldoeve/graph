#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

struct Edge{
    int destination, weight, reverse;
    bool state;
    int index;
    mutable int flow = 0;
    Edge(int d, int w, int r, bool s, int i): 
        destination(d), weight(w), reverse(r), state(s), index(i){;}
    bool operator< (const Edge& other)const{
        return this->destination < other.destination;
    } 
};

using Graph = std::vector<std::set<Edge>>*;

Graph constructGraph(unsigned long int& map, int& edges)
{
    int source, destination, weight;
    int numOfState, size;
    unsigned long int math = 1;
    unsigned long int seen = 0;

    std::cin >> size;
    Graph game = new std::vector<std::set<Edge>>;
    game->resize(size);

    for(int i = 0; i < 2; ++i){
        std::cin >> numOfState;
        edges = numOfState;
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

            (*game)[source].emplace(temp);
            (*game)[destination].emplace(temp2);
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
    return (*game)[--count].begin()->index;
}

bool levelGraphConstruction(int* level ,Graph game, const int source, const int sink)
{
    for(unsigned int i = 0; i < game->size(); ++i)
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
                std::set<Edge>::iterator temp = (*game)[i->destination].find(Edge{i->reverse, 0, 0, 0, 0});
                std::set<Edge>::iterator end = (*game)[i->destination].end();
                if(temp != end){
                    (*temp).flow -= recurseFlow;
                }
                return recurseFlow;
            }
        }
    }
    return 0;
}

void maxflow(Graph game, int data[2] , const int source, const int sink)
{
    data[0] = -1; data[1] = -1;
    if(source == sink) return;
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

int sheild()
{
    unsigned long map = 0;
    int edges = 0;
    Graph game = constructGraph(map, edges);
    if(map > 0) return leafSelection(map, game);
    std::vector<int> counts(edges, 0);

    return std::distance(std::begin(counts), std::max_element(std::begin(counts), std::end(counts)));
}

int cut()
{
    unsigned long int map = 0;
    int edges = 0;
    Graph game = constructGraph(map, edges);
    if(map > 0) return leafSelection(map, game);
    std::vector<int> counts(edges, 0);

    int index = (int) std::distance(std::begin(counts), std::max_element(std::begin(counts), std::end(counts)));
    counts[index] = 0;
    return (int) std::distance(std::begin(counts), std::max_element(std::begin(counts), std::end(counts)));
}

int main(int argc, char* argv[])
{
    if(argc != 2) return 0;
    int choosenEdge = strcmp(argv[1], "short\n") ? sheild():cut();
    std::cout << choosenEdge << std::endl;
    return 0;
}