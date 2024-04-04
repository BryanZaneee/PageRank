#include "pagerank.h"
#include <iostream>
#include <string>

int main() {
    int no_of_lines, power_iterations;
    std::string from, to;

    // Read the number of lines (edges) and the number of power iterations
    std::cin >> no_of_lines >> power_iterations;

    // Create an instance of AdjacencyList
    AdjacencyList graph;

    // Read each edge and add it to the graph
    for (int i = 0; i < no_of_lines; i++) {
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    // Run the PageRank algorithm
    graph.PageRank(power_iterations);

    return 0;
}

