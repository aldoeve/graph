#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int spanningTreeFinder(unsigned long int answer[3], unsigned long int minMaxSpanCost[2], int order, int** adjMatrix);

int nextOrder()
{
    char start = '.';
    int order = 0;
    for(int i = 0; i < 100000 && start != '/'; ++i)
        std::cin >> start;
    std::cin >> order;
    return order;
}

int **nextMatrix(int order)
{
    int temp = 0;
    int ** adjMatrix = new int*[order];
    for(int i = 0; i < order; ++i)
        adjMatrix[i] = new int[order];
    for(int i = 0; i < order; ++i){
        for(int j = 0; j < order; ++j){
            std::cin >> temp;
            adjMatrix[i][j] = temp;
        }
    }
    return adjMatrix;
}

TEST_CASE("CHECK if all spanning trees are present"){
    long unsigned int answers[3] = {0};
    long unsigned int minMaxSpanCost[2] = {0};
    int order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 0);
        REQUIRE(answers[1] == 0);
        REQUIRE(answers[2] == 0);
        REQUIRE(minMaxSpanCost[0] == 0);
        REQUIRE(minMaxSpanCost[1] == 0);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 16);
        REQUIRE(answers[1] == 16);
        REQUIRE(answers[2] == 16);
        REQUIRE(minMaxSpanCost[0] == 3);
        REQUIRE(minMaxSpanCost[1] == 3);
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    memset(answers, 0, sizeof(answers));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 3);
        REQUIRE(answers[2] == 3);
        REQUIRE(minMaxSpanCost[0] == 2);
        REQUIRE(minMaxSpanCost[1] == 2);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 0);
        REQUIRE(answers[1] == 0);
        REQUIRE(answers[2] == 0);
        REQUIRE(minMaxSpanCost[0] == 0);
        REQUIRE(minMaxSpanCost[1] == 0);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 1);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 1);
        REQUIRE(minMaxSpanCost[1] == 1);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 3);
        REQUIRE(answers[2] == 3);
        REQUIRE(minMaxSpanCost[0] == 2);
        REQUIRE(minMaxSpanCost[1] == 2);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 125);
        REQUIRE(answers[1] == 125);
        REQUIRE(answers[2] == 125);
        REQUIRE(minMaxSpanCost[0] == 4);
        REQUIRE(minMaxSpanCost[1] == 4);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 1296);
        REQUIRE(answers[1] == 1296);
        REQUIRE(answers[2] == 1296);
        REQUIRE(minMaxSpanCost[0] == 5);
        REQUIRE(minMaxSpanCost[1] == 5);
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    memset(answers, 0, sizeof(answers));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 1);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 2);
        REQUIRE(minMaxSpanCost[1] == 2);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 45);
        REQUIRE(answers[1] == 45);
        REQUIRE(answers[2] == 45);
        REQUIRE(minMaxSpanCost[0] == 4);
        REQUIRE(minMaxSpanCost[1] == 4);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 3);
        REQUIRE(answers[2] == 3);
        REQUIRE(minMaxSpanCost[0] == 3);
        REQUIRE(minMaxSpanCost[1] == 3);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 3);
        REQUIRE(answers[2] == 3);
        REQUIRE(minMaxSpanCost[0] == 4);
        REQUIRE(minMaxSpanCost[1] == 4);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 3);
        REQUIRE(answers[2] == 3);
        REQUIRE(minMaxSpanCost[0] == 3);
        REQUIRE(minMaxSpanCost[1] == 3);
}
TEST_CASE("CHECK with self-loops"){
    int order;
    long unsigned int answers[3];
    long unsigned int minMaxSpanCost[2] = {0};
    memset(answers, 0, sizeof(answers));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 3);
        REQUIRE(answers[2] == 3);
        REQUIRE(minMaxSpanCost[0] == 2);
        REQUIRE(minMaxSpanCost[1] == 2);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 16);
        REQUIRE(answers[1] == 16);
        REQUIRE(answers[2] == 16);
        REQUIRE(minMaxSpanCost[0] == 3);
        REQUIRE(minMaxSpanCost[1] == 3);
}
TEST_CASE("CHECK with weights"){
    int order;
    long unsigned int answers[3];
    long unsigned int minMaxSpanCost[2] = {0};
    memset(answers, 0, sizeof(answers));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 4);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 21);
        REQUIRE(minMaxSpanCost[1] == 27);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 11);
        REQUIRE(minMaxSpanCost[1] == 15);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 11);
        REQUIRE(minMaxSpanCost[1] == 15);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 10);
        REQUIRE(minMaxSpanCost[1] == 20);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 1);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 150);
        REQUIRE(minMaxSpanCost[1] == 150);
}
TEST_CASE("CHECK if algo can find multiple min and max spans"){
    int order;
    long unsigned int answers[3];
    long unsigned int minMaxSpanCost[2] = {0};
    memset(answers, 0, sizeof(answers));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 2);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 13);
        REQUIRE(minMaxSpanCost[1] == 17);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 3);
        REQUIRE(answers[1] == 1);
        REQUIRE(answers[2] == 2);
        REQUIRE(minMaxSpanCost[0] == 10);
        REQUIRE(minMaxSpanCost[1] == 11);
    memset(answers, 0, sizeof(answers));
    memset(minMaxSpanCost, 0, sizeof(minMaxSpanCost));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 12);
        REQUIRE(answers[1] == 2);
        REQUIRE(answers[2] == 1);
        REQUIRE(minMaxSpanCost[0] == 30);
        REQUIRE(minMaxSpanCost[1] == 35);
}
TEST_CASE("CHECK if the algo can handle large graphs using the formula n^(n-2) to verify edges of spans"){
    int order;
    long unsigned int answers[3];
    long unsigned int minMaxSpanCost[2] = {0};
    memset(answers, 0, sizeof(answers));
    order = nextOrder();
    spanningTreeFinder(answers, minMaxSpanCost, order, nextMatrix(order));
        REQUIRE(answers[0] == 262144);
        REQUIRE(answers[1] == 262144);
        REQUIRE(answers[2] == 262144);
        REQUIRE(minMaxSpanCost[0] == 7);
        REQUIRE(minMaxSpanCost[1] == 7);
}