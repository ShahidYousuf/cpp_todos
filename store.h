//
// Created by Shahid Yousuf on 20/10/22.
//

#ifndef CPP_TODOS_STORE_H
#define CPP_TODOS_STORE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "todo.h"

class Store {

public:
    enum Persistence {
        FILE,
        DB
    };
    Store(Persistence persistence): _persistence(persistence) {
        if (_persistence == Store::Persistence::FILE) {
            init_current_index();
        }
    };
//    ~Store() {
//        save_current_index();
//    }

    void save(Todo &todo) {
        switch (_persistence) {
            case Persistence::FILE:
                return save_to_file(todo);
            case Persistence::DB:
                return save_to_db(todo);
            default:
                return save_to_file(todo);
        }
    }

    std::vector<Todo> list() {
        switch (_persistence) {
            case Persistence::FILE:
                return list_from_file();
            case Persistence::DB:
                return list_from_file();
            default:
                return list_from_file();
        }
    }

    Todo get(int id) {
        switch (_persistence) {
            case Persistence::FILE:
                return get_from_file(id);
            case Persistence::DB:
                return get_from_file(id);
            default:
                return get_from_file(id);
        }
    }


private:
    Persistence _persistence;
    int current_file_index;
    std::string default_file_db {".todo_db"};
    std::string default_file_index_db {".todo_db_index"};

    void save_to_file(Todo &todo) {
        int todo_id = current_file_index + 1;
        todo.id(todo_id);
        std::ofstream fout(default_file_db, std::ios_base::app);
        fout << todo.id() << " " << todo.title() << " " << todo.completed() << "\n";
        fout.close();
        current_file_index  = todo_id;
        save_current_index();
    }

    std::vector<Todo> list_from_file() {
        std::vector<Todo> todos;
        std::string currentLine;
        std::ifstream fin(default_file_db);
        while(getline(fin, currentLine)) {
            Todo currentTodo;
            int id;
            std::string title;
            int _completed = std::stoi(currentLine.substr(currentLine.length()-1));
            bool  completed = _completed == 1 ? true : false;
            int index = currentLine.find(' ');
            id = std::stoi(currentLine.substr(0, index));
            title = currentLine.substr(index, currentLine.length()-1-index );
            currentTodo.id(id);
            currentTodo.title(title);
            currentTodo.completed(completed);
            todos.push_back(currentTodo);
        }
        fin.close();
        return todos;
    }

    Todo get_from_file(int id) {
        Todo todo;
        std::string currentLine;
        std::ifstream fin(default_file_db);
        while(getline(fin, currentLine)) {
            int index = currentLine.find(' ');
            int t_id = std::stoi(currentLine.substr(0, index));
            if (t_id == id) {
                todo.id(id);
                int _completed = std::stoi(currentLine.substr(currentLine.length() - 1));
                bool t_completed = _completed == 1 ? true : false;
                todo.completed(t_completed);
                std::string t_title = currentLine.substr(index, currentLine.length() - 1 - index);
                todo.title(t_title);
                break;
            }
        }
        fin.close();
        return todo;
    }

    void save_to_db(Todo &todo) {
        std::cout << "Saving todo " << todo.title() << " to database\n";
    }

    void init_current_index() {
        std::ifstream fin(default_file_index_db);
        int current_index;
        fin >> current_index;
        fin.close();
        current_file_index = current_index;
    }

    void save_current_index() {
        std::ofstream fout(default_file_index_db);
        fout << current_file_index;
        fout.close();
    }



};
#endif //CPP_TODOS_STORE_H
