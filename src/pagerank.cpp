#include "pagerank.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unordered_set>

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

// Initializes the Pagerank scores to 1/n, and collects unique node names
void AdjacencyList::initializeRanks() {
    // Use a set to collect all unique node names from both 'from' and 'to' nodes
    std::unordered_set<std::string> uniqueNodes;
    for (const auto& edge : graph) {
        uniqueNodes.insert(edge.first); // Insert 'from' node
        for (const auto& dest : edge.second) {
            uniqueNodes.insert(dest); // Insert 'to' nodes
        }
    }

    // Calculate the initial rank as 1/N
    float initialRank = 1.0f / uniqueNodes.size();
    for (const auto& node : uniqueNodes) {
        ranks[node] = initialRank; // Initialize rank for each unique node
    }

    // Also update the outDegree for nodes that have no outgoing edges (i.e., not present in 'graph')
    for (const auto& node : uniqueNodes) {
        if (graph.find(node) == graph.end()) {
            graph[node] = std::vector<std::string>(); // Insert a node with an empty edge list
            outDegree[node] = 0; // This node has no outgoing edges
        }
    }
}

// Calculates the outdegree for each node in the graph
void AdjacencyList::calculateOutDegree() {
    for (const auto& node : graph) {
        outDegree[node.first] = node.second.size();
    }
}

// Performs the powerIterations based on the value of p
void AdjacencyList::powerIteration(int p) {
    if (p == 1) {
        // If p is 1, print the initialized ranks and return
        std::vector<std::pair<std::string, float>> sortedRanks(ranks.begin(), ranks.end());
        std::sort(sortedRanks.begin(), sortedRanks.end());
        for (const auto& rank : sortedRanks) {
            std::cout << rank.first << " " << std::fixed << std::setprecision(2) << rank.second << "\n";
        }
        return; // No need to perform any iterations since p = 1
    }

    // If p is not 1, perform the power iteration as usual
    std::unordered_map<std::string, float> newRanks;
    // this "p-1" fix solved all of my issues lmao
    for (int i = 0; i < p-1; ++i) {
        // Initialize newRanks for the current iteration
        for (const auto& node : ranks) { // Use ranks instead of graph to include all nodes
            newRanks[node.first] = 0.0f;
        }

        // Calculate the rank contributions for each node
        for (const auto& node : graph) {
            float rankContribution = ranks[node.first] / outDegree[node.first];
            for (const auto& dest : node.second) {
                newRanks[dest] += rankContribution;
            }
        }

        // Update ranks for the next iteration
        ranks.swap(newRanks);
    }

    // After the final iteration, sort and print the ranks
    std::vector<std::pair<std::string, float>> sortedRanks(ranks.begin(), ranks.end());
    std::sort(sortedRanks.begin(), sortedRanks.end());
    for (const auto& rank : sortedRanks) {
        std::cout << rank.first << " " << std::fixed << std::setprecision(2) << rank.second << "\n";
    }
}

// The master function that combines the three prior to enact the PageRank algorithm
void AdjacencyList::PageRank(int p) {
    initializeRanks();
    calculateOutDegree();
    powerIteration(p);
}

