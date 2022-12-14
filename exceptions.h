//
// Created by Shahid Yousuf on 22/10/22.
//

#ifndef CPP_TODOS_EXCEPTIONS_H
#define CPP_TODOS_EXCEPTIONS_H
#include <iostream>

class TodoNotFoundException : public std::exception {
private:
    int _todo_id;
public:
    TodoNotFoundException(int todo_id): _todo_id(todo_id) {}
    std::string what() {
        return "No Todo found for id " + std::to_string(_todo_id);
    }
};

class HomeEnvNotFoundException : public std::exception {
public:
    std::string what() {
        return "Cannot read environment variable HOME, have you set it?\n";
    }
};

#endif //CPP_TODOS_EXCEPTIONS_H
