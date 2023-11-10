cmake_minimum_required(VERSION 3.26)
project(PageRank)

# Pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 17)

# Create a library target for the PageRank algorithm to be used by both the main application and tests
add_library(pagerank_lib
        src/pagerank.cpp
        src/pagerank.h)

# Create the main application executable
add_executable(Main
        src/main.cpp)

# Link the main application executable to the PageRank library
target_link_libraries(Main PRIVATE pagerank_lib)

# Create the test executable
add_executable(Tests
        testing/Testing.cpp)

# Link the test executable to the Catch2 testing library and the PageRank library
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain pagerank_lib)
