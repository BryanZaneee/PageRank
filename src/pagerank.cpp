#include "pagerank.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

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
    // placeholder for PageRank calculation logic.
    std::unordered_map<std::string, float> newRanks;

    // Perform power iterations
    for (int i = 0; i < p; ++i) {
        // Initialize newRanks for the current iteration
        for (auto& rank : ranks) {
            newRanks[rank.first] = 0.0f;
        }
        // Distribute ranks over outgoing links
        for (const auto& node : graph) {
            float rankContribution = ranks[node.first] / outDegree[node.first];
            for (const auto& dest : node.second) {
                newRanks[dest] += rankContribution;
            }
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
