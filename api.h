//
// Created by Shahid Yousuf on 22/10/22.
//

#ifndef CPP_TODOS_API_H
#define CPP_TODOS_API_H
#include <iostream>
#include <vector>
#include "todo.h"
#include "store.h"
#include "exceptions.h"

class Controller {
public:
    Controller(Store &store): _store(store) {}

    void create() {
        std::string title;
        bool completed { false };
        std::cout << "Enter todo title: ";
        std::getline(std::cin, title);
        if(title.empty() || title.length() < 1) {
            throw std::invalid_argument("Todo title cannot be empty");
        }
        Todo todo = Todo(title, completed);
        _store.save(todo);
    }

    void list() {
        auto todos = _store.list();
        for (auto todo: todos) {
            std::cout << todo;
        }
    }

    void get() {
        std::cout << "Enter todo id to fetch its details ";
        int id;
        std::cin >> id;
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        Todo todo = _store.get(id);
        if (todo.title().empty() || todo.title().length() < 1) {
            throw TodoNotFoundException(id);
        }
        std::cout << todo;
    }

    void remove() {
        std::cout << "Enter todo id to remove: ";
        int id;
        std::cin >> id;
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        _store.remove(id);
        std::cout << "Todo with id " << id << " removed successfully\n";
    }

    void check() {
        std::cout << "Enter todo id to mark as checked (complete): ";
        int id;
        std::cin >> id;
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        _store.check(id);
        std::cout << "Todo with id " << id << " checked (completed) successfully\n";
    }

    void uncheck() {
        std::cout << "Enter todo id to mark as unchecked (mark pending): ";
        int id;
        std::cin >> id;
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        _store.uncheck(id);
        std::cout << "Todo with id " << id << " unchecked (marked pending) successfully\n";
    }

    void edit() {
        std::cout << "Enter todo id to edit the title: ";
        int id;
        std::string title;
        std::cin >> id;
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        Todo todo = _store.get(id);
        if (todo.title().empty() || todo.title().length() < 1) {
            throw TodoNotFoundException(id);
        }
        std::cout << "You are editing the following todo.\n" << todo;
        std::cout << "Enter new title: ";
        // get rid of white space that previous std::cin call ignores and leaves as garbage
        std::getline(std::cin >> std::ws, title);
        if(title.empty() || title.length() < 1) {
            throw std::invalid_argument("Todo title cannot be empty");
        }
        _store.edit(id, title);
        std::cout << "Todo with id " << id << " edited successfully\n";
    }

private:
    Store _store;
};

#endif //CPP_TODOS_API_H
