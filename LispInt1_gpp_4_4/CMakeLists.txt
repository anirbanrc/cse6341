project(lispint1)

add_executable(lispint1 tree_utils.cpp io_return.cpp lispio.cpp se.cpp main.cpp)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

