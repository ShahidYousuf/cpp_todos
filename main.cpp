#include <iostream>
#include <array>
#include "todo.h"
#include "command.h"
#include "api.h"
#include "exceptions.h"


int main(int argc, char *argv[]) {
    std::string title {"Sample todo title"};
    bool completed {true};

    Store store = Store(Store::Persistence::FILE);
    Controller controller = Controller(store);

    std::array<std::string, 6> commands {"get", "list", "create", "edit", "delete", "done"};
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
            try {
                controller.create();
            }catch (std::invalid_argument &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }catch (std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "get") {
            try {
                controller.get();
            }catch (TodoNotFoundException &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }catch (std::invalid_argument &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "list") {
            controller.list();
        } else if (command == "edit") {

        } else if (command == "delete") {
            try {
                controller.remove();
            }catch (TodoNotFoundException &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }catch (std::invalid_argument &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (command == "done") {

        }


    }
    //Todo todo = Todo(title, completed);
    //std::cout << "Title: " << todo.title() << " Completed: " << todo.completed() << "\n";

    return 0;
}
