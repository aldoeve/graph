#ifndef EDGE
#define EDGE
#include <iostream>

struct Edge
{
    int source;
    int destination;
    int weight;
    Edge(int s, int d, int w):source(s), destination(d), weight(w){;}
};

std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
    return os << "<" << edge.source << ", " << edge.destination << ">" << std::endl;
}

#endif