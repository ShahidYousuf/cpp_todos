//
// Created by Shahid Yousuf on 28/10/22.
//

#ifndef CPP_TODOS_ROUTER_H
#define CPP_TODOS_ROUTER_H
#include "api.h"
class Router {
public:

    void route(Controller controller, CommandWithOptions commandWithOptions) {
        auto command = commandWithOptions.command();
        switch (command) {
            case Command::LIST:
                return route_list(controller, commandWithOptions);
            case Command::GET:
                return route_get(controller, commandWithOptions);
            case Command::CREATE:
                return route_create(controller, commandWithOptions);
            case Command::EDIT:
                return route_edit(controller, commandWithOptions);
            case Command::DELETE:
                return route_delete(controller, commandWithOptions);
            case Command::CHECK:
                return route_check(controller, commandWithOptions);
            case Command::UNCHECK:
                return route_uncheck(controller, commandWithOptions);
            case Command::HELP:
                return route_help(controller, commandWithOptions);
            default:
                return controller.help();
        }
    }

private:
    void route_list(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto option = options.find(Option::STATUS);
        if (option == options.end()) {
            controller.list();
            return;
        }
        auto value = options[Option::STATUS];
        if (value == "completed") {
            controller.list_complete();
            return;
        }
        if (value == "pending") {
            controller.list_pending();
            return;
        }
        controller.list();
    }

    void route_get(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto option = options.find(Option::INDEX);
        if (option == options.end()) {
            controller.help();
            return;
        }
        auto value = options[Option::INDEX];
        if (!check_valid_index(value)) {
            controller.help();
            return;
        }
        int id = std::stoi(value);
        if (id <= 0) {
            controller.help();
            return;
        }
        controller.get(id);
    }

    void route_create(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto title_option = options.find(Option::TITLE);
        if (title_option == options.end()) {
            controller.help();
            return;
        }
        std::string title = options[Option::TITLE];
        if (!check_valid_title(title)) {
            controller.help();
            return;
        }
        controller.create(title);
    }

    void route_edit(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto index_option = options.find(Option::INDEX);
        auto title_option = options.find(Option::TITLE);
        if (index_option == options.end()) {
            controller.help();
            return;
        }
        if (title_option == options.end()) {
            controller.help();
            return;
        }
        auto index = options[Option::INDEX];
        if (!check_valid_index(index)) {
            controller.help();
            return;
        }
        int id = std::stoi(index);
        if (id <= 0) {
            controller.help();
            return;
        }
        std::string title = options[Option::TITLE];
        if (!check_valid_title(title)) {
            controller.help();
            return;
        }
        controller.edit(id, title);
    }

    void route_delete(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto option = options.find(Option::INDEX);
        if (option == options.end()) {
            controller.help();
            return;
        }
        auto index = options[Option::INDEX];
        if (!check_valid_index(index)) {
            controller.help();
            return;
        }
        int id = std::stoi(index);
        if (id <= 0) {
            controller.help();
            return;
        }
        controller.remove(id);
    }

    void route_check(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto option = options.find(Option::INDEX);
        if (option == options.end()) {
            controller.help();
            return;
        }
        auto index = options[Option::INDEX];
        if (!check_valid_index(index)) {
            controller.help();
            return;
        }
        int id = std::stoi(index);
        if (id <= 0) {
            controller.help();
            return;
        }
        controller.check(id);
    }

    void route_uncheck(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto option = options.find(Option::INDEX);
        if (option == options.end()) {
            controller.help();
            return;
        }
        auto index = options[Option::INDEX];
        if (!check_valid_index(index)) {
            controller.help();
            return;
        }
        int id = std::stoi(index);
        if (id <= 0) {
            controller.help();
            return;
        }
        controller.uncheck(id);
    }

    void route_help(Controller &controller, CommandWithOptions &commandWithOptions) {
        auto options = commandWithOptions.options();
        auto option = options.find(Option::COMMAND);
        if (option == options.end()) {
            controller.help();
            return;
        }
        auto value = options[Option::COMMAND];
        auto command = getBaseCommand(value);
        controller.help(command);
    }

    bool check_valid_index(std::string &index) {
        std::string::const_iterator it = index.cbegin();
        while (it != index.cend() && std::isdigit(*it)) ++it;
        return !index.empty() && it == index.cend();
    }

    bool check_valid_title(std::string &title) {
        if (title.empty() || title.length() < 1 || title.length() > 80) {
            return false;
        }
        return true;
    }

};
#endif //CPP_TODOS_ROUTER_H
