# Quiz_project
This project contains txt, json and yml files with 14 questions. The user answers the question and gets a point for the correct answer.

    Requirements

To run this program, you need the following:

- Compiler: GCC (tested on Linux, but should work on other systems with GCC as well).
- CMake: The project uses CMake for building.
- Libraries: The program uses external libraries for JSON and YAML file parsing:
        nlohmann/json (https://github.com/nlohmann/json) for JSON parsing.
        yaml-cpp (https://github.com/jbeder/yaml-cpp) for YAML parsing.

    Installation

Linux (Ubuntu/Debian):
1. Install the required packages (GCC, CMake, and necessary libraries):
    sudo apt-get update
    sudo apt-get install g++ cmake
2. Clone the repository from GitHub:
    git clone <repository_link>
3. Navigate to the project directory:
    cd QuizApp
4. Create a build directory and run CMake:
    mkdir build
    cd build
    cmake ..
5. Compile the project:
    make
6. Run the program:
    ./QuizApp

Windows:

1. Install a GCC-compatible environment (e.g., MinGW (https://sourceforge.net/projects/mingw/) or Cygwin (https://www.cygwin.com/)).
2. Install CMake:
        Download and install CMake from the official website (https://cmake.org/download/).
3. Clone the repository from GitHub:
    git clone <repository_link>
4. Open a terminal (Git Bash, Command Prompt, or Cygwin), and navigate to the project directory:
    cd QuizApp
5. Create a build directory and run CMake:
    mkdir build
    cd build
    cmake ..
6. Compile the project using the MinGW GCC compiler:
    mingw32-make

7. Run the program:
    ./QuizApp.exe

    Additional Notes
- The quiz data is stored in three formats: JSON (quiz.json), YAML (quiz.yml), and plain text (quiz.txt).
- Ensure that the required JSON and YAML libraries are available. CMake will automatically download and link them as part of the build process using FetchContent.
- App in this version has to run from the root dir of the project.