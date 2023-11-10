#ifndef PAGERANK_PAGERANK_H
#define PAGERANK_PAGERANK_H

#include <string>
#include <vector>
#include <unordered_map>

class AdjacencyList {
private:
    // This graph is an adjacency list, where each key is a string for a webpage
    // and the values are a vector of strings for the webpages the key points to
    std::unordered_map<std::string, std::vector<std::string>> graph;

    // This is a map that holds the PageRank scores
    std::unordered_map<std::string, float> ranks;

    // This map keeps track of the outbound links for each webpage
    std::unordered_map<std::string, int> outDegree;

    // some helper functions
    void initializeRanks(int n);
    void calculateOutDegree();
    void powerIteration(int p);

public:
    AdjacencyList() = default;
    void addEdge(const std::string& from, const std::string& to);
    void PageRank(int p);
};

#endif //PAGERANK_PAGERANK_H
