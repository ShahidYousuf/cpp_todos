#include <iostream>
#include <array>
#include "todo.h"
#include "command.h"
#include "api.h"

int main(int argc, char *argv[]) {
    std::string title {"Sample todo title"};
    bool completed {true};

    Store store = Store(Store::Persistence::FILE);
    Controller controller = Controller(store);

    std::array<std::string, 5> commands {"get", "list", "create", "edit", "delete"};
    if (argc == 1) {
        std::cout << "Please issue one of the following commands:\n";
        for (const auto c: commands) {
            std::cout << c << "\n";
        }
    }
    if(argc > 1) {
        std::string command = argv[1];
        auto command_found = std::find(commands.cbegin(), commands.cend(), command);
        if (command_found == commands.cend()) {
            std::cout << "Invalid command " << command << "\n";
        }

        if (command == "create") {
            controller.create();
        } else if (command == "get") {
            std::cout << "Getting todo\n";
        } else if (command == "list") {
            controller.list();
        } else if (command == "edit") {
            std::cout << "Editing todo\n";
        } else if (command == "delete") {
            std::cout << "Deleting todo\n";
        }


    }
    //Todo todo = Todo(title, completed);
    //std::cout << "Title: " << todo.title() << " Completed: " << todo.completed() << "\n";

    return 0;
}
