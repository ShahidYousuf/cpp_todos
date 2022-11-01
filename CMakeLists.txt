cmake_minimum_required(VERSION 3.23)
project(cpp_todos)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)

add_executable(todo main.cpp todo.h store.h command.h api.h exceptions.h router.h)
