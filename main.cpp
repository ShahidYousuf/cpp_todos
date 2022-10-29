#include <iostream>
#include <array>
#include "command.h"
#include "api.h"
#include "exceptions.h"
#include "router.h"


int main(int argc, char *argv[]) {

    Store store = Store(Store::Persistence::FILE);
    Controller controller = Controller(store);

    std::vector<std::string> input_commands;
    for (int i = 0; i < argc; ++i) {
        auto input_command = argv[i];
        input_commands.emplace_back(input_command);
    }
    auto commandWithOptions = getCommand(input_commands);
    Router router = Router();
    try {
        router.route(controller, commandWithOptions);
    } catch (TodoNotFoundException &e) {
        std::cerr << "Error: " << e.what() << "\n";
    } catch (std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << "\n";
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
