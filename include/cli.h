#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <iostream>

#include "utils.h"
#include "task.h"
#include "json.h"

class CLI {
public:
    CLI(const std::string &filename);
    void addTask(const std::string &description);
    void listTasks();
    void deleteTasks(int id);
    void updateTasks(int id, std::string &description);
    void markInProgress(int id);
    void markDone(int id);
    void listTasksByStatus(const std::string &status);

    inline void printCommands() {
        std::cout << "Commands:\n"
                  << "\t              add : Initialize a new task\n"
                  << "\t             list : List all tasks with their details including ID, description, status, creation time, and update time\n"
                  << "\t           delete : Delete a task by its ID\n"
                  << "\t           update : Update a task's description by its ID\n"
                  << "\t mark-in-progress : Mark a task as \"in progress\" by its ID\n"
                  << "\t        mark-done : Mark a task as \"done\" by its ID\n"
                  << "\t     list + statu : List tasks filtered by their status\n";
    }

private:
    std::vector<Task> tasks;
    std::string jsonFile;
};

#endif // CLI_H