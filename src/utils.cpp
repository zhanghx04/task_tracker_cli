#include <sstream>
#include <algorithm>  // for std::max

#include "utils.h"

/**
 * @brief Get the current time as a string in the format "MM-DD-YYYY HH:MM:SS"
 * @return string type timestamp
 */
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &nowTime);
#else
    localtime_r(&nowTime, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%m-%d-%Y %H:%M:%S");
    std::string currentTime = oss.str();

    return currentTime;
}

int getLastId(const std::string &filename) {
    int maxId = 0;
    std::vector<Task> tasks = parseJsonFile(filename);

    for (const Task &task : tasks) {
        maxId = std::max(maxId, task.id);
    }

    return maxId;
}