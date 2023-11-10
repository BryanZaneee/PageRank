#include "../src/pagerank.cpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

// Helper function to capture the output of PageRank
std::string capturePageRankOutput(AdjacencyList& graph, int iterations) {
    std::ostringstream stream;
    // Redirect cout to our stringstream buffer or any other stream
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(stream.rdbuf());

    // Run PageRank which will 'cout' the results
    graph.PageRank(iterations);

    // Restore old cout stream buffer
    std::cout.rdbuf(oldCoutStreamBuf);

    return stream.str();
}

TEST_CASE("PageRank Calculation", "[PageRank]") {
    // Redirect cout to capture output
    std::stringstream buffer;
    std::streambuf* prevCout = std::cout.rdbuf(buffer.rdbuf());

    // Create a graph and add edges according to the input
    AdjacencyList graph;
    graph.addEdge("google.com", "gmail.com");
    graph.addEdge("google.com", "maps.com");
    graph.addEdge("facebook.com", "ufl.edu");
    graph.addEdge("ufl.edu", "google.com");
    graph.addEdge("ufl.edu", "gmail.com");
    graph.addEdge("maps.com", "facebook.com");
    graph.addEdge("gmail.com", "maps.com");

    // Run the PageRank algorithm with 2 iterations
    graph.PageRank(2);

    // Restore the original buffer before reading the output
    std::cout.rdbuf(prevCout);

    // Capture the output
    std::string output = buffer.str();

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
    REQUIRE(output == "A 0.00\nB 1.00\n");
}

TEST_CASE("Two Nodes with Repeat Links", "[PageRank]") {
    AdjacencyList graph;
    graph.addEdge("A", "B");
    graph.addEdge("A", "B"); // Repeat link
    std::string output = capturePageRankOutput(graph, 2);
    REQUIRE(output == "A 0.00\nB 1.00\n");
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
