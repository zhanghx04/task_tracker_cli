#include <cassert>

#include "cli.h"

/**
 * @brief Constructor for the CLI class
 * 
 * @param filename The name of the JSON file to store tasks
 * 
 * Initializes a new CLI instance with the specified JSON filename for task storage
 */
CLI::CLI(const std::string &filename) : jsonFile(filename) {}


/**
 * @brief Initialize a new task
 * 
 * @param description The description of the task
 */
void CLI::addTask(const std::string &description) {
    Task task;

    task.id = getLastId(jsonFile) + 1;
    task.description = description;
    task.status = TODO;
    task.createdAt = getCurrentTime();
    task.updatedAt = getCurrentTime();

    writeTaskToJson(&task, jsonFile);
}


/**
 * @brief List all tasks with their details including ID, description, status, creation time, and update time
 * 
 * If the tasks vector is empty, loads tasks from the JSON file first.
 * For each task, displays:
 * - Task ID and description
 * - Current status
 * - Creation timestamp
 * - Last update timestamp
 */
void CLI::listTasks() {
    std::cout << "List of Tasks: " << std::endl;

    if (tasks.empty()) {
        tasks = parseJsonFile(jsonFile);
    } 

    for (const Task &task : tasks) {
        if (!task.description.empty()) {
            std::cout << task.id << ". " << task.description << std::endl;
            std::cout << "Task status   : " << task.status << std::endl;
            std::cout << "Task createdAt: " << task.createdAt << std::endl;
            std::cout << "Task updatedAt: " << task.updatedAt << std::endl;
            std::cout << std::endl;
        } else {
            std::cout << "The task[" << task.id << "] has no description. " << std::endl;
        }
    }
}


/**
 * @brief Delete a task by its ID
 * 
 * @param id The ID of the task to delete
 * 
 * Searches for a task with the given ID in the tasks vector and removes it.
 * After deletion, creates a new temporary JSON file with the remaining tasks,
 * then replaces the original JSON file with the updated one.
 */
void CLI::deleteTasks(int id) {
    if (tasks.empty()) {
        tasks = parseJsonFile(jsonFile);
    }

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            break;
        }
    }

    updateJsonFile(tasks, jsonFile);
}


/**
 * @brief Update a task's description by its ID
 * 
 * @param id The ID of the task to update
 * @param description The new description to set for the task
 * 
 * Finds the task with the given ID in the tasks vector and updates its description.
 * Also updates the task's updatedAt timestamp. After updating, creates a new temporary 
 * JSON file with all tasks including the updated one, then replaces the original JSON file.
 */
void CLI::updateTasks(int id, std::string &description) {
    if (tasks.empty()) {
        tasks = parseJsonFile(jsonFile);
    }

    for (auto &task : tasks) {
        if (task.id == id) {
            task.description = description;
            task.updatedAt = getCurrentTime();
            break;
        }
    }

    updateJsonFile(tasks, jsonFile);
}


/**
 * @brief Mark a task as "in progress" by its ID
 * 
 * @param id The ID of the task to mark as in progress
 * 
 * Finds the task with the given ID in the tasks vector and updates its status to IN_PROGRESS.
 * After updating, creates a new temporary JSON file with all tasks including the updated one,
 * then replaces the original JSON file.
 */
void CLI::markInProgress(int id) {
    if (tasks.empty()) {
        tasks = parseJsonFile(jsonFile);
    }

    for (auto &task : tasks) {
        if (task.id == id) {
            task.status = IN_PROGRESS;
            break;
        }
    }

    updateJsonFile(tasks, jsonFile);
}

/**
 * @brief Mark a task as "done" by its ID
 * 
 * @param id The ID of the task to mark as done
 * 
 * Finds the task with the given ID in the tasks vector and updates its status to DONE.
 * After updating, creates a new temporary JSON file with all tasks including the updated one,
 * then replaces the original JSON file.
 */
void CLI::markDone(int id) {
    if (tasks.empty()) {
        tasks = parseJsonFile(jsonFile);
    }

    for (auto &task : tasks) {
        if (task.id == id) {
            task.status = DONE;
            break;
        }
    }

    updateJsonFile(tasks, jsonFile);
}


/**
 * @brief List tasks filtered by their status
 * 
 * @param status The status to filter tasks by (TODO, IN_PROGRESS, or DONE)
 * 
 * Retrieves all tasks from the JSON file if tasks vector is empty.
 * Filters and displays tasks matching the provided status.
 * For each matching task, prints its ID, description, status, creation time,
 * and last update time.
 */
void CLI::listTasksByStatus(const std::string &status) {
    assert((status == TODO || status == IN_PROGRESS || status == DONE) && "Invalid status provided.");

    if (tasks.empty()) {
        tasks = parseJsonFile(jsonFile);
    }

    for (const auto &task : tasks) {
        if (task.status == status) {
            std::cout << task.id << ". " << task.description << std::endl;
            std::cout << "Task status   : " << task.status << std::endl;
            std::cout << "Task createdAt: " << task.createdAt << std::endl;
            std::cout << "Task updatedAt: " << task.updatedAt << std::endl;
            std::cout << std::endl;
        }
    }
}