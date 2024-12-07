//
//  main.cpp
//  task_tracker_cli
//
//  Created by Haoxiang Zhang on 12/2/24.
//

#include <iostream>
#include <string>
#include <vector>

#include "cli.h"

// Command line arguments
struct CommandLineArgs {
    std::string command;
    std::vector<std::string> args;
};


/**
 * @brief Parse command line arguments into a CommandLineArgs structure
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return CommandLineArgs structure containing the parsed command and arguments
 *
 * Takes the raw command line arguments and organizes them into a CommandLineArgs
 * structure with the first argument as the command and subsequent arguments stored
 * in the args vector.
 */
CommandLineArgs parseCommandLineArgs(int argc, const char *argv[]) {
    CommandLineArgs args;

    if (argc > 1) {
        args.command = argv[1];
        for (int i = 2; i < argc; ++i) {
            args.args.push_back(argv[i]);
        }
    }

    return args;
}

int main(int argc, const char * argv[]) {
    // Parse the command line data from the inputs
    CommandLineArgs args = parseCommandLineArgs(argc, argv);

    if (args.command.empty()) {
        std::cerr << "ERROR: No command specified.\n";
        return 1;
    }

    // Processing CLI
    CLI taskManager("tasks.json");

    if (args.command == "add") {
        taskManager.addTask(args.args[0]);
    }
    else if (args.command == "list") {
        if (args.args.empty()) {
            taskManager.listTasks();
        } else {
            taskManager.listTasksByStatus(args.args[0]);
        }
    } 
    else if (args.command == "delete") {
        taskManager.deleteTasks(std::stoi(args.args[0]));
    } 
    else if (args.command == "update") {
        taskManager.updateTasks(std::stoi(args.args[0]), args.args[1]);
    } 
    else if (args.command == "mark-in-progress") {
        taskManager.markInProgress(std::stoi(args.args[0]));
    } 
    else if (args.command == "mark-done") {
        taskManager.markDone(std::stoi(args.args[0]));
    } 
    else {
        std::cerr << "ERROR: Invalid command. Please run choose the existing commands: \n";
        taskManager.printCommands();
        return -1;
    }

    return 0;
}
