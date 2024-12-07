#include "json.h"

/**
 * @brief Write the information from the task to the file with a certain format
 * 
 * @param task It is a Task type data structure which stores some task information
 * @param filename The pointer pointed to the filename
 */
void writeTaskToJson(const  Task *task, const std::string &filename) {
    std::string jsonContent;
    std::ifstream file(filename);

    if (file.good()) {
        auto begin = std::istreambuf_iterator<char>(file);
        auto end =  std::istreambuf_iterator<char>();
        jsonContent = std::string(begin, end);
        file.close();
    }

    std::string newTaskJson = "\n\t{\n"
                              "\t\t\"id\": " + std::to_string(task->id) + ",\n"
                              "\t\t\"description\": \"" + task->description + "\",\n"
                              "\t\t\"status\": \"" + task->status + "\",\n"
                              "\t\t\"createdAt\": \"" + task->createdAt + "\",\n"
                              "\t\t\"updatedAt\": \"" + task->updatedAt + "\",\n"
                              "\t}\n";

    if (!jsonContent.empty()) {
        size_t start_pos = jsonContent.find_last_of('[') + 1;
        size_t end_pos = jsonContent.find_last_of(']');
        if (start_pos != std::string::npos && end_pos != std::string::npos) {
            if (start_pos < end_pos) {  // Check if there are existing items
                jsonContent.insert(end_pos, "," + newTaskJson);
            } else {
                jsonContent.insert(end_pos, newTaskJson);
            }
        }
    } else {
        jsonContent = "[" + newTaskJson + "]";
    }

    std::ofstream file_out(filename, std::ios::trunc);
    file_out << jsonContent;
    file_out.close();
}


void updateJsonFile(const std::vector<Task> &tasks, std::string &jsonFile) {
    // Create a new JSON file for storing updated tasks
    const std::string tmpFile = "tmp.json";
    for (const auto &task : tasks) {
        writeTaskToJson(&task, tmpFile);
    }

    // Replace the original tasks JSON file with the tmp file
    remove(jsonFile.c_str());
    rename(tmpFile.c_str(), jsonFile.c_str());
}


/**
 * @brief Parse a JSON file and get the Task objects from JSON file to a vector
 * 
 * @param filename The JSON file name
 * @return A vector of Task object
 */
std::vector<Task> parseJsonFile(const std::string &filename) {
    std::vector<Task> tasks;

    std::ifstream file(filename);
    auto begin = std::istreambuf_iterator<char>(file);
    auto end = std::istreambuf_iterator<char>();
    std::string jsonContent(begin, end);
    file.close();

    size_t start_pos = jsonContent.find('[') + 1;
    size_t end_pos = jsonContent.find_last_of(']');

    if (start_pos != std::string::npos && end_pos != std::string::npos) {
        std::string tasksJson = jsonContent.substr(start_pos, end_pos - start_pos);

        size_t task_start_pos = 0;
        size_t task_end_pos = tasksJson.find('}');

        while (task_end_pos != std::string::npos) {
            std::string curr_taskJson = tasksJson.substr(task_start_pos, task_end_pos - task_start_pos + 1);

            Task task;

            /* Get the task information */
            // id
            size_t id_start_pos = curr_taskJson.find("\"id\": ") + 6;
            size_t id_end_pos = curr_taskJson.find(',', id_start_pos);
            task.id = std::stoi(curr_taskJson.substr(id_start_pos, id_end_pos - id_start_pos));

            // description
            size_t description_start_pos = curr_taskJson.find("\"description\": \"") + 16;
            size_t description_end_pos = curr_taskJson.find(',', description_start_pos);
            task.description = curr_taskJson.substr(description_start_pos, description_end_pos - description_start_pos - 1);

            // status
            size_t status_start_pos = curr_taskJson.find("\"status\": \"") + 11;
            size_t status_end_pos = curr_taskJson.find(',', status_start_pos);
            task.status = curr_taskJson.substr(status_start_pos, status_end_pos - status_start_pos - 1);
            
            // createdAt
            size_t createdAt_start_pos = curr_taskJson.find("\"createdAt\": \"") + 14;
            size_t createdAt_end_pos = curr_taskJson.find(',', createdAt_start_pos);
            task.createdAt = curr_taskJson.substr(createdAt_start_pos, createdAt_end_pos - createdAt_start_pos - 1);

            // updatedAt
            size_t updatedAt_start_pos = curr_taskJson.find("\"updatedAt\": \"") + 14;
            size_t updatedAt_end_pos = curr_taskJson.find(',', updatedAt_start_pos);
            task.updatedAt = curr_taskJson.substr(updatedAt_start_pos, updatedAt_end_pos - updatedAt_start_pos - 1);


            /* Collect and update */
            tasks.push_back(task);

            task_start_pos = task_end_pos + 1;
            task_end_pos = tasksJson.find('}', task_start_pos);
        }
    }

    return tasks;
}