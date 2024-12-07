#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

#define TODO "todo"
#define IN_PROGRESS "in-progress"
#define DONE "done"

struct Task {
    int id;
    std::string description;
    std::string status;
    std::string createdAt;
    std::string updatedAt;
};

#endif // TASK_H