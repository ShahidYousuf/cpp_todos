//
// Created by Shahid Yousuf on 22/10/22.
//

#ifndef CPP_TODOS_API_H
#define CPP_TODOS_API_H
#include <iostream>
#include <vector>
#include "todo.h"
#include "store.h"

class Controller {
public:
    Controller(Store &store): _store(store) {}

    void create() {
        std::string title;
        bool completed { false };
        std::cout << "Enter todo title: ";
        std::getline(std::cin, title);
        if(title.empty() || title.length() < 1) {
            throw "Todo title cannot be empty";
        }
        Todo todo = Todo(title, completed);
        _store.save(todo);
    }

    void list() {
        auto todos = _store.list();
        for (auto todo: todos) {
            std::cout << todo.id() << " " << todo.title() << " " << todo.completed() << "\n";
        }
    }
private:
    Store _store;
};

#endif //CPP_TODOS_API_H
