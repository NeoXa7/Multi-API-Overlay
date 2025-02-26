#include "DataManager.h"

namespace DataManager
{
    void create_directory_with_file(const std::string& dir_name)
    {
        if (!std::filesystem::exists(dir_name)) {
            std::filesystem::create_directory(dir_name);
        }
    }

    void save_renderer_api_config(std::string api)
    {
        std::string filePath = "bin/configuration.ini";
        create_directory_with_file("bin");

        std::ofstream file(filePath, std::ios::out);

        if (file.is_open()) {
            file << "Renderer : " << api << '\n';
            file.close();
        }
    }

    std::string get_api()
    {
        std::filesystem::path filePath = "bin/logs.ini";
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filePath << '\n';
            return "None";
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.rfind("Renderer : ", 0) == 0) { // Check if line starts with "Renderer="
                return line.substr(11); // Extract value after '='
            }
        }

        return "None";
    }
}