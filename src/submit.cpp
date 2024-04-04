#include <iostream>
#include <iomanip>
#include <algorithm>
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


// This function will add an edge from "from" to "to" in the graph
void AdjacencyList::addEdge(const std::string& from, const std::string& to) {
    graph[from].push_back(to);
    // Ensure all nodes are in the ranks map, even if they have no outgoing links
    if (ranks.find(from) == ranks.end()) {
        ranks[from] = 0.0f;
    }
    if (ranks.find(to) == ranks.end()) {
        ranks[to] = 0.0f;
    }
}

// Initializes the Pagerank scores to 1/n
// "n" is number of nodes!!
void AdjacencyList::initializeRanks(int n) {
    float initialRank = 1.0f / graph.size();
    for (auto& rank : ranks) {
        rank.second = initialRank;
    }
}

// Calculates the outdegree for each node in the graph
void AdjacencyList::calculateOutDegree() {
    for (const auto& node : graph) {
        outDegree[node.first] = node.second.size();
    }
}

// ranks importance of elements in the graph
void AdjacencyList::powerIteration(int p) {
    std::unordered_map<std::string, float> newRanks;

    // Perform power iterations
    for (int i = 0; i < p; ++i) {
        float danglingRankSum = 0.0f;

        // Initialize newRanks for the current iteration
        for (const auto& node : graph) {
            newRanks[node.first] = 0.0f;
        }

        // Calculate the rank contributions for each node
        for (const auto& node : graph) {
            if (outDegree[node.first] == 0) {
                // Handle dangling nodes by distributing their rank evenly
                danglingRankSum += ranks[node.first] / graph.size();
            } else {
                float rankContribution = ranks[node.first] / outDegree[node.first];
                for (const auto& dest : node.second) {
                    newRanks[dest] += rankContribution;
                }
            }
        }

        // Add the dangling rank sum to each node
        for (auto& rank : newRanks) {
            rank.second += danglingRankSum;
        }

        // Normalization step
        float totalRank = 0.0f;
        for (const auto& rank : newRanks) {
            totalRank += rank.second;
        }
        for (auto& rank : newRanks) {
            rank.second /= totalRank;
        }

        // Update ranks for the next iteration
        ranks = newRanks;
    }
}


// The function that takes all other functions to do the PageRank algorithm
void AdjacencyList::PageRank(int p) {
    // graph.size is representing n
    initializeRanks(graph.size());
    calculateOutDegree();
    powerIteration(p);

    // Print the PageRank in alphabetical order
    std::vector<std::pair<std::string, float>> sortedRanks(ranks.begin(), ranks.end());
    std::sort(sortedRanks.begin(), sortedRanks.end());

    for (const auto& rank : sortedRanks) {
        std::cout << rank.first << " " << std::fixed << std::setprecision(2) << rank.second << std::endl;
    }
}