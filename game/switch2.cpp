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
        bool state = i == 0 ? true : false;
        for(int j = 0; j < numOfState; ++j){
            std::cin >> source >> destination >> weight;
            --source; --destination;
            if(state) weight = INT32_MAX;
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

std::list<int> maxflow(Graph game, int source, int sink)
{
    std::list<int> cutset;
    if(source == sink) return cutset;
    int answer = 0;
    int level[game->size()];
    
    while(levelGraphConstruction(level, game, source, sink)){
        for(int flow = pushFlow(source, sink, INT32_MAX, game, level); flow != 0; flow = pushFlow(source, sink, flow, game, level))
            answer += flow;
    }

    for(uint i = 0; i < (*game).size(); ++i){
        for(auto j = (*game)[i].begin(); j != (*game)[i].end(); ++j){
            if(j->weight - j->flow == 0 && j->state == false)
                cutset.push_back(j->index);
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
    std::list<int> leafs;
    findLeafs(leafs, game);
    if(!leafs.empty())
        solution  = leafs.front();
    else{
        std::list<int> cutset;
        int smallestSeen = INT32_MAX;
        int size = (int)(game->size());
        bool memo[size][size] = {};
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                if(memo[i][j] == 0 or memo[i][j] == 0){
                    memo[i][j] = 1; memo[i][j] = 1;
                    std::list<int> check = maxflow(game, i, j);
                    if((int)(check.size()) < smallestSeen && check.size() != 0)
                        cutset = check;
                }
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
    return shield();
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
//0.00053966325