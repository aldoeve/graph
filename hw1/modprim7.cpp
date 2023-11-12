#include <iostream>
#include <list>
#include <queue>
#include <set>
#include "edge.h"
//#include "printG.h" //only when needed
using BList = std::list<std::list<Edge>*>;

void recurse(const int & size, int** adjMatrix, BList& bigList, Edge edge, std::set<int> visited, std::list<Edge> path, std::queue<Edge> todo)
{
    if(visited.find(edge.destination) != visited.end()) return;

    visited.emplace(edge.destination);
    path.push_back(edge);

    for(int i = 0; i < size; ++i){
        if(adjMatrix[edge.destination][i] > 0 && visited.find(i) == visited.end() && visited.size() != (std::size_t)(size)){
            Edge a(edge.destination, i, adjMatrix[edge.destination][i]);
            todo.push(a);
        }
    }

    while(todo.size() > 0 && visited.size() != (std::size_t)(size)){
        Edge next  = todo.front();
        todo.pop();
        recurse(size, adjMatrix, bigList, next, visited, path, todo);
    }

    std::list<Edge>* copy = new std::list<Edge>;
    *copy = path;
    bigList.push_back(copy);
}

int singularTreeCost(std::list<Edge>& tree)
{
    int cost = 0;
    for(auto i = ++(tree.begin()); i != tree.end(); ++i)
        cost += (*i).weight;
    return cost;
}

int spanningTreeFinder(unsigned long int answer[3], unsigned long int minMaxSpanCost[2], int order, int** adjMatrix)
{
    if(order == 0 || order == 1){
        for(int i = 0; i < order; ++i)
            delete[] adjMatrix[i];
        delete [] adjMatrix;
        return 0;
    }

    BList bigList;
    std::set<int> vistited;
    std::list<Edge> path;
    std::queue<Edge> todo;
    Edge edge(0, 0, 0);

    recurse(order, adjMatrix, bigList, edge, vistited, path, todo);
    BList min, max;
    int seenMin, seenMax;
    seenMax = seenMin = 0;

    int cost = 0;
    int numOfSpanTrees = 0;
    for(auto i = bigList.begin(); i != bigList.end(); ++i){
        if((**i).size() == (std::size_t)(order)){
            ++numOfSpanTrees;
            cost = singularTreeCost((**i));
            if(min.size() == 0 && max.size() == 0){
                seenMin = cost;
                seenMax = cost;
            }
            if(seenMin > cost){
                min.clear();
                seenMin = cost;
            }
            if(seenMax < cost){
                max.clear();
                seenMax = cost;
            }
            if (seenMin == cost){
                min.push_back((*i));
            }
            if(seenMax == cost){
                max.push_back(*i);
            }
        }
    }

    answer[0] = numOfSpanTrees;
    answer[1] = min.size();
    answer[2] = max.size();
    minMaxSpanCost[0] = seenMin;
    minMaxSpanCost[1] = seenMax;

    for(auto i = bigList.begin(); i != bigList.end(); ++i)
        delete *i;
    for(int i = 0; i < order; ++i)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    return 0;
}