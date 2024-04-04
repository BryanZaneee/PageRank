#ifndef PAGERANK_PAGERANK_H
#define PAGERANK_PAGERANK_H

#include <unordered_map>
#include <string>
#include <vector>

class AdjacencyList {
private:
    // graph: Represents the adjacency list. Each key is a string representing a webpage.
    // The corresponding value is a vector of strings representing webpages that the key webpage points to.
    std::unordered_map<std::string, std::vector<std::string>> graph;

    // ranks: Stores the PageRank scores. Each key is a webpage, and the value is its PageRank score.
    std::unordered_map<std::string, float> ranks;

    // outDegree: Tracks the number of outbound links for each webpage.
    // The key is the webpage, and the value is the count of outbound links.
    std::unordered_map<std::string, int> outDegree;

    // Helper functions to initialize ranks, calculate outDegrees, and perform the power iteration method.
    void initializeRanks();
    void calculateOutDegree();
    void powerIteration(int p);

public:
    // Constructor: Initializes an empty AdjacencyList object.
    AdjacencyList() = default;

    // addEdge: Adds a directed edge from 'from' to 'to' in the graph.
    void addEdge(const std::string& from, const std::string& to);

    // PageRank: Computes the PageRank scores using the power iteration method.
    // 'p' specifies the number of iterations for the power iteration.
    void PageRank(int p);
};

#endif // PAGERANK_PAGERANK_H
