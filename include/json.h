#ifndef JSON_H
#define JSON_H

#include <fstream>
#include "task.h"

void writeTaskToJson(const struct Task *task, const std::string &filename);
void updateJsonFile(const std::vector<Task> &tasks, std::string &jsonFile);
std::vector<Task> parseJsonFile(const std::string &filename);

#endif // JSON_H