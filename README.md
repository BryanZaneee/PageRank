# PageRank Algorithm Implementation

This project implements the PageRank algorithm, widely recognized for its use by Google Search to rank web pages in their search engine results. This C++ implementation allows the user to understand the importance of various nodes in a network, mimicking the way web pages gain prominence based on their link structure.

## CMake

The PageRank project leverages CMake as its build system, which streamlines the compilation process across various platforms. CMake automatically manages the discovery and configuration of dependencies and compiler settings, ensuring a smooth build process with little to no manual setup required.

## Getting it Running!

To build the project, you must first ensure that all dependencies are in place:

- **CMake**: Install the most recent version of CMake (3.14 or higher is recommended). It's available on the [CMake official website](https://cmake.org/download/).
- **Compiler**: A C++17 standard-compliant compiler is necessary. For macOS, Clang included with Xcode works well, while on Windows, you might opt for MinGW or Visual Studio.
- **Catch2**: The project uses Catch2 for unit testing. The CMake configuration is designed to fetch this dependency automatically. Should you need to install it manually, refer to the [Catch2 GitHub repository](https://github.com/catchorg/Catch2).

With the dependencies ready and the repository cloned on your local machine, you can build the PageRank program by following these steps:

1. Open your terminal and navigate to the project's root directory.
2. Run `mkdir build` to create a new build directory if it doesn't already exist.
3. Change into the build directory using `cd build`.
4. Execute `cmake ..` to configure the project and generate the build system in the build directory.
5. Run `make` to compile the project using the generated makefile.
6. The `PageRank` executable will be located within the build directory upon successful compilation.

## Usage

After building the project, execute the `PageRank` program found in the build directory. The application calculates the PageRank of various nodes and outputs the scores, which can be directed to a file for further analysis or visualization. For a detailed guide on how to use the application and interpret the results, refer to the project documentation.

Thank you for exploring this implementation of the PageRank algorithm, and enjoy analyzing the importance of nodes in your network!
