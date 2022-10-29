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
#include "command.h"

class Controller {
public:
    Controller(Store &store): _store(store) {}

    void help() {
        std::cout << "Help: Please use one of the following commands.\n";
        std::cout << Command::LIST << " " << Command::GET << " " << Command::CREATE << " ";
        std::cout << Command::EDIT << " " << Command::DELETE << " " << Command::CHECK << " ";
        std::cout << Command::UNCHECK << " " << Command::HELP << "\n";
        std::cout << "To know more about a command, enter\n";
        std::cout << "todo help -c [command]\ntodo help --command [command]\n";
    }

    void help(Command command) {
        switch (command) {
            case Command::LIST:
                return help_list();
            case Command::GET:
                return help_get();
            case Command::CREATE:
                return help_create();
            case Command::EDIT:
                return help_edit();
            case Command::DELETE:
                return help_delete();
            case Command::CHECK:
                return help_check();
            case Command::UNCHECK:
                return help_uncheck();
            case Command::HELP:
                return help();
            default:
                return help();
        }
    }

    void help_get() {
        std::cout << "Get a todo with a given unique id.\n";
        std::cout << "Format:\n";
        std::cout << "todo get -i | --index <unique id>\n";
        std::cout << "Examples:\n";
        std::cout << "todo get -i 5\t - get todo with id 5\n";
        std::cout << "todo get --index 5\t - get todo with id 5\n";
    }

    void help_list() {
        std::cout << "List all todos, optionally excepts options to list completed or pending only todos.\n";
        std::cout << "Format:\n";
        std::cout << "todo list [-s | --status [completed | pending]]\n";
        std::cout << "Examples:\n";
        std::cout << "todo list\t - list all todos\n";
        std::cout << "todo list -s completed\t - list all completed todos.\n";
        std::cout << "todo list -s pending\t - list all pending todos.\n";
        std::cout << "todo list --status pending\t - list all pending todos.\n";
    }
    void help_create() {
        std::cout << "Create a new todo with a valid title.\n";
        std::cout << "Format:\n";
        std::cout << "todo create -t | --title \"<todo title here>\"\n";
        std::cout << "Examples:\n";
        std::cout << "todo create -t \"A sample todo item\"\t - creates a new todo with the given title.\n";
        std::cout << "todo create --title \"A sample todo item\"\t - creates a new todo with the given title.\n";
    }
    void help_edit() {
        std::cout << "Edits a todo title using a valid unique id\n";
        std::cout << "Format:\n";
        std::cout << "todo edit -i | --index <unique id> -t | --title \"<new todo title here>\"\n";
        std::cout << "Examples:\n";
        std::cout << "todo edit -i 5 -t \"A sample todo item edited\"\t - edits todo title with the given id\n";
        std::cout << "todo edit --index 5 --title \"A sample todo item edited\"\t - edits todo title with the given id\n";
    }
    void help_delete() {
        std::cout << "Delete a todo with a given id\n";
        std::cout << "Format:\n";
        std::cout << "todo delete -i | --index <unique id>\n";
        std::cout << "Examples:\n";
        std::cout << "todo delete -i 5\t - delete todo with the given id.\n";
        std::cout << "todo delete --index 5\t - delete todo with the given id.\n";
    }
    void help_check() {
        std::cout << "Checks or marks a todo complete with a given id.\n";
        std::cout << "Format:\n";
        std::cout << "todo check -i | --index <unique id>\n";
        std::cout << "Examples:\n";
        std::cout << "todo check -i 5\t - checks or marks todo with given id as complete.\n";
        std::cout << "todo check --index 5\t - checks or marks todo with given id as complete.\n";
    }

    void help_uncheck() {
        std::cout << "Unchecks or marks a todo pending/incomplete with a given id.\n";
        std::cout << "Format:\n";
        std::cout << "todo uncheck -i | --index <unique id>\n";
        std::cout << "Examples:\n";
        std::cout << "todo uncheck -i 5\t - unchecks or marks todo with given id as pending/incomplete.\n";
        std::cout << "todo uncheck --index 5\t - unchecks or marks todo with given id as pending/incomplete.\n";
    }

    void create(std::string title) {
        bool completed { false };
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

    void list_complete() {
        auto todos = _store.list();
        for (auto todo: todos) {
            if (!todo.completed()) {
                continue;
            }
            std::cout << todo;
        }
    }

    void list_pending() {
        auto todos = _store.list();
        for (auto todo: todos) {
            if (todo.completed()) {
                continue;
            }
            std::cout << todo;
        }
    }

    void get(int id) {
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        Todo todo = _store.get(id);
        if (todo.title().empty() || todo.title().length() < 1) {
            throw TodoNotFoundException(id);
        }
        std::cout << todo;
    }

    void remove(int id) {
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        _store.remove(id);
        std::cout << "Todo with id " << id << " removed successfully\n";
    }

    void check(int id) {
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        _store.check(id);
        std::cout << "Todo with id " << id << " checked (completed) successfully\n";
    }

    void uncheck(int id) {
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        _store.uncheck(id);
        std::cout << "Todo with id " << id << " unchecked (marked pending) successfully\n";
    }

    void edit(int id, std::string title) {
        if (id <=0) {
            throw std::invalid_argument("Invalid value for id");
        }
        Todo todo = _store.get(id);
        if (todo.title().empty() || todo.title().length() < 1) {
            throw TodoNotFoundException(id);
        }
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
