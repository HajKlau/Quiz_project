cmake_minimum_required(VERSION 3.14)

project(QuizApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5  
)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.7.0  
)

FetchContent_MakeAvailable(json yaml-cpp)

add_executable(QuizApp main.cpp questions.cpp utility.cpp)

target_link_libraries(QuizApp PRIVATE nlohmann_json::nlohmann_json yaml-cpp)

