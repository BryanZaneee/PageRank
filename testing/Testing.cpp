#include "../src/pagerank.h"  // Ensure this path is correct
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <iostream>

// Helper function to capture the output of PageRank
std::string capturePageRankOutput(AdjacencyList& graph, int iterations) {
    std::ostringstream stream;
    // Redirect cout to our stringstream buffer
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(stream.rdbuf());

    // Run PageRank which will 'cout' the results
    graph.PageRank(iterations); // Use the PageRank method as defined in your source code

    // Restore old cout stream buffer
    std::cout.rdbuf(oldCoutStreamBuf);

    return stream.str();
}

TEST_CASE("PageRank Calculation", "[PageRank]") {
    AdjacencyList graph;
    graph.addEdge("google.com", "gmail.com");
    graph.addEdge("google.com", "maps.com");
    graph.addEdge("facebook.com", "ufl.edu");
    graph.addEdge("ufl.edu", "google.com");
    graph.addEdge("ufl.edu", "gmail.com");
    graph.addEdge("maps.com", "facebook.com");
    graph.addEdge("gmail.com", "maps.com");

    // Capture the output
    std::string output = capturePageRankOutput(graph, 2);

    // Define the expected output
    std::string expectedOutput =
            "facebook.com 0.20\n"
            "gmail.com 0.20\n"
            "google.com 0.10\n"
            "maps.com 0.30\n"
            "ufl.edu 0.20\n";

    // Compare the captured output to the expected output
    REQUIRE(output == expectedOutput);
}

TEST_CASE("No Input (Empty Graph)", "[PageRank]") {
    AdjacencyList graph;
    std::string output = capturePageRankOutput(graph, 2);
    REQUIRE(output.empty());
}

TEST_CASE("Single Node (Self-loop)", "[PageRank]") {
    AdjacencyList graph;
    graph.addEdge("A", "A");
    std::string output = capturePageRankOutput(graph, 2);
    REQUIRE(output == "A 1.00\n");
}

TEST_CASE("Two Nodes with a Single Direction Link", "[PageRank]") {
    AdjacencyList graph;
    graph.addEdge("A", "B");
    std::string output = capturePageRankOutput(graph, 2);
    REQUIRE(output == "A 0.00\nB 0.50\n");
}

TEST_CASE("Two Nodes with Repeat Links", "[PageRank]") {
    AdjacencyList graph;
    graph.addEdge("A", "B");
    graph.addEdge("A", "B"); // Repeat link
    std::string output = capturePageRankOutput(graph, 2);
    REQUIRE(output == "A 0.00\nB 0.50\n");
}

TEST_CASE("Circular Reference Between Three Nodes", "[PageRank]") {
    AdjacencyList graph;
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("C", "A");
    std::string output = capturePageRankOutput(graph, 2);
    // The output here may vary depending on the convergence of the PageRank algorithm
    // with only two iterations. You might need to adjust the expected output based on your implementation.
    REQUIRE(output == "A 0.33\nB 0.33\nC 0.33\n");
}

TEST_CASE("PageRank with Different Power Iterations", "[PageRank]") {
    SECTION("2 Iterations") {
        AdjacencyList graph;
        graph.addEdge("A", "B");
        graph.addEdge("B", "C");
        graph.addEdge("C", "A");
        std::string output = capturePageRankOutput(graph, 2);
        REQUIRE(output == "A 0.33\nB 0.33\nC 0.33\n");
    }

    SECTION("5 Iterations") {
        AdjacencyList graph;
        graph.addEdge("A", "B");
        graph.addEdge("B", "C");
        graph.addEdge("C", "A");
        std::string output = capturePageRankOutput(graph, 5);
        // Expected output might need adjustment based on the convergence of the algorithm
        REQUIRE(output == "A 0.33\nB 0.33\nC 0.33\n");
    }

    SECTION("10 Iterations") {
        AdjacencyList graph;
        graph.addEdge("A", "B");
        graph.addEdge("B", "A");
        std::string output = capturePageRankOutput(graph, 10);
        REQUIRE(output == "A 0.50\nB 0.50\n");
    }

    SECTION("100 Iterations") {
        AdjacencyList graph;
        graph.addEdge("X", "Y");
        graph.addEdge("Y", "Z");
        graph.addEdge("Z", "X");
        std::string output = capturePageRankOutput(graph, 100);
        // The output for 100 iterations may be more converged compared to fewer iterations
        REQUIRE(output == "X 0.33\nY 0.33\nZ 0.33\n");
    }
}

TEST_CASE("PageRank Test Case", "[PageRank]") {
    AdjacencyList graph;

    // Add edges as per the test case
    graph.addEdge("go", "man");
    graph.addEdge("go", "plan");
    graph.addEdge("joker", "go");
    graph.addEdge("plan", "man");

    // Run the PageRank algorithm with 3 iterations
    std::string output = capturePageRankOutput(graph, 3);

    // Define the expected output
    std::string expectedOutput =
            "go 0.00\n"
            "joker 0.00\n"
            "man 0.25\n"
            "plan 0.12\n";

    // Compare the captured output to the expected output
    REQUIRE(output == expectedOutput);
}
