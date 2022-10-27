//
// Created by Shahid Yousuf on 20/10/22.
//

#ifndef CPP_TODOS_TODO_H
#define CPP_TODOS_TODO_H
#include <iostream>

class Todo {
private:
    int _id {};
    std::string _title {};
    bool _completed { false };

public:
    Todo() = default;
    Todo(std::string &title):
        _title(title), _completed(false)
    {}
    Todo(std::string &title, bool completed):
        _title(title), _completed(completed)
    {}

    int id() {
        return _id;
    }

    const std::string &title() {
        return _title;
    }

    const bool &completed() {
        return _completed;
    }

    void id(int &value) {
        _id = value;
    }

    void title(std::string &value) {
        _title = value;
    }

    void completed(bool value) {
        _completed = value;
    }

};

std::ostream& operator << (std::ostream &out, Todo &todo) {
    auto status = todo.completed() ? "\033[1;32m completed\033[0m" : "\033[1;33m pending\033[0m";
    auto id = "\033[1;34m" + std::to_string(todo.id()) + "\033[0m";
    out << id << " " << todo.title() << status << "\n";
    return out;
}

#endif //CPP_TODOS_TODO_H
