#include "pagerank.h"
#include <iostream>

//int main() {
    int no_of_lines, power_iterations;
    std::string from, to;
    std::cin >> no_of_lines >> power_iterations;
    AdjacencyList graph;

    for(int i = 0; i < no_of_lines; i++) {
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    graph.PageRank(power_iterations);
    return 0;
}
