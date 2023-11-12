#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <set>
#include <queue>
#include "stdint.h"

struct Edge{
    int destination;
    int weight;
    bool state;
    int index;
    int flow = 0;
    Edge(int d, int w, bool s, int i): destination(d), weight(w), state(s), index(i){;}
};

std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
    return os << edge.destination << edge.weight << std::endl;
}

using Graph = std::vector<std::list<Edge>>;

Graph* constructGraph()
{
    int numofState;
    int source, destination, weight;
    Graph* graph = new Graph;
    (*graph).resize(100);

    for(int i = 0; i < 2; ++i){
        std::cin >> numofState;
        bool state = i == 0 ? true : false;
        for(int j = 0; j < numofState; ++j){
            std::cin >> source >> destination >> weight;
            Edge temp(destination, weight, state, j);
            Edge temp2(source, weight, state, j);
            (*graph)[source].push_back(temp);
            (*graph)[destination].push_back(temp2);
        }
    }

    return graph;
}

void printGraph(Graph* graph)
{
    for(uint i = 0; i < (*graph).size(); ++i){
        if(!(*graph)[i].empty()){
            for(auto j = (*graph)[i].begin(); j != (*graph)[i].end(); ++j){
                std::cout << i;
                std::cout << *j;
            }
        }
    }
}

void printLevel(std::vector<int>& level)
{
    for(int i = 0; i < 100; ++i){
        if(level[i] >-1){
            std::cout << i << ' ' << level[i] << std::endl;
        }
    }
}
//finds the unprotected leaf nodes
std::vector<int> findLeafNodes(Graph* graph)
{
    std::vector<int> leafs;

    for(uint i = 0; i < (*graph).size(); ++i){
        if((*graph)[i].size() == 1 && (*graph)[i].front().state == false)
            leafs.emplace_back((*graph)[i].front().index);
    }

    return leafs;
}

bool levelGraphConstruction(std::vector<int>& level, Graph* graph, const int source, const int sink)
{
    level[source] = 0;
    std::queue<int> todo;
    std::set<int> seen;
    seen.insert(source);
    todo.push(source);
    while(!todo.empty()){
        int current = todo.front();
        todo.pop();
        for(auto i = (*graph)[current].begin(); i != (*graph)[current].end(); ++i){
            if(seen.find(i->destination) == seen.end()){
                seen.insert(i->destination);
                todo.push(i->destination);
                level[i->destination] = level[current] + 1;
            }
        }
    }
    return seen.find(sink) != seen.end();
}

int maxflow(Graph* graph,const int source, const int sink)
{
    int answer = INT32_MAX;
    
    std::vector<int> level(100, -1);
    levelGraphConstruction(level, graph, source, sink);
       

    return answer;
}

int cut()
{
   Graph * graph = constructGraph();
    int solution = 0;
    std::vector<int> leafs = findLeafNodes(graph);
    if(leafs.size() != 0)
        solution = leafs.front();
    else
        solution = maxflow(graph, 1, 2);
    delete graph;
    return solution; 
}

int shield()
{
    Graph * graph = constructGraph();
    int solution = 0;
    std::vector<int> leafs = findLeafNodes(graph);
    if(leafs.size() != 0)
        solution = leafs.front();
    else
        solution = maxflow(graph, 1, 5);
    delete graph;
    return solution;
}

int main(int argc, char * argv[])
{
    if(argc != 2){std::cout << "Error: Missing input\n"; return 0;}
    int edgeModified = strcmp(argv[1], "short\n") ? shield() : cut();
    std::cout << edgeModified << std::endl;
}