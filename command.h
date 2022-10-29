//
// Created by Shahid Yousuf on 22/10/22.
//

#ifndef CPP_TODOS_COMMAND_H
#define CPP_TODOS_COMMAND_H
#include <iostream>
#include <vector>
#include <map>


enum Command {
    GET,
    LIST,
    CREATE,
    EDIT,
    DELETE,
    CHECK,
    UNCHECK,
    HELP
};

std::ostream& operator << (std::ostream& out, Command command) {
    switch (command) {
        case Command::LIST :
            out << "\033[1;32m list\033[0m";
            break;
        case Command::GET:
            out << "\033[1;32m get\033[0m";
            break;
        case Command::CREATE:
            out << "\033[1;32m create\033[0m";
            break;
        case Command::EDIT:
            out << "\033[1;32m edit\033[0m";
            break;
        case Command::DELETE:
            out << "\033[1;32m delete\033[0m";
            break;
        case Command::CHECK:
            out << "\033[1;32m check\033[0m";
            break;
        case Command::UNCHECK:
            out << "\033[1;32m uncheck\033[0m";
            break;
        case Command::HELP:
            out << "\033[1;32m help\033[0m";
            break;
        default:
            out << "\033[1;32m help\033[0m";
            break;
    }
    return out;
}

enum Option {
    INDEX,
    TITLE,
    STATUS,
    COMMAND,
    NONE,
};

Option getOption(std::string &value) {
    Option option {Option::NONE};
    if (value == "-s" || value == "--status") {
        option = Option::STATUS;
    }
    if (value == "-i" || value == "--index") {
        option = Option::INDEX;
    }
    if (value == "-t" || value == "--title") {
        option = Option::TITLE;
    }
    if (value == "-c" || value == "--command") {
        option = Option::COMMAND;
    }
    return option;
}

class CommandWithOptions {
private:
    Command _command {Command::HELP};
    std::map<Option, std::string> _options;
public:
    CommandWithOptions(Command command): _command(command) {};

    void command(Command value) {
        _command = value;
    }

    Command command() {
        return _command;
    }

    void option(Option o, std::string &value) {
        _options.insert({o, value});
    }

    std::map<Option, std::string>& options() {
        return _options;
    }

    void clear_options() {
        _options.clear();
    }
};

Command getBaseCommand(std::string &command) {
    if (command == "list") {
        return Command::LIST;
    } else if (command == "get") {
        return Command::GET;
    }else if (command == "create") {
        return Command::CREATE;
    } else if (command == "edit") {
        return Command::EDIT;
    } else if (command == "delete") {
        return Command::DELETE;
    } else if (command == "check") {
        return Command::CHECK;
    } else if (command == "uncheck") {
        return Command::UNCHECK;
    } else if (command == "help") {
        return Command::HELP;
    }
    return Command::HELP;
}

CommandWithOptions getCommand(std::vector<std::string> &arguments) {
    std::string command = arguments[1];
    CommandWithOptions commandWithOptions = CommandWithOptions(Command::HELP);
    if (command == "list") {
        auto option = getOption(arguments[2]);
        auto value = arguments[3];
        commandWithOptions.command(Command::LIST);
        commandWithOptions.clear_options();
        commandWithOptions.option(option, value);
    } else if (command == "get") {
        auto option = getOption(arguments[2]);
        auto value = arguments[3];
        commandWithOptions.command(Command::GET);
        commandWithOptions.clear_options();
        commandWithOptions.option(option, value);
    }else if (command == "create") {
            auto option = getOption(arguments[2]);
            auto title = arguments[3];
            commandWithOptions.command(Command::CREATE);
            commandWithOptions.clear_options();
            commandWithOptions.option(option, title);
    } else if (command == "edit") {
        auto option1 = getOption(arguments[2]);
        auto index = arguments[3];
        auto option2 = getOption(arguments[4]);
        auto title = arguments[5];
        commandWithOptions.command(Command::EDIT);
        commandWithOptions.clear_options();
        commandWithOptions.option(option1, index);
        commandWithOptions.option(option2, title);
    } else if (command == "delete") {
        auto option = getOption(arguments[2]);
        auto index = arguments[3];
        commandWithOptions.command(Command::DELETE);
        commandWithOptions.clear_options();
        commandWithOptions.option(option, index);
    } else if (command == "check") {
        auto option = getOption(arguments[2]);
        auto index = arguments[3];
        commandWithOptions.command(Command::CHECK);
        commandWithOptions.clear_options();
        commandWithOptions.option(option, index);
    } else if (command == "uncheck") {
        auto option = getOption(arguments[2]);
        auto index = arguments[3];
        commandWithOptions.command(Command::UNCHECK);
        commandWithOptions.clear_options();
        commandWithOptions.option(option, index);
    } else if (command == "help") {
        auto option = getOption(arguments[2]);
        auto value = arguments[3];
        commandWithOptions.command(Command::HELP);
        commandWithOptions.clear_options();
        commandWithOptions.option(option, value);
    }
    return commandWithOptions;
}


#endif //CPP_TODOS_COMMAND_H
