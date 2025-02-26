#include "DataManager.h"

namespace DataManager
{
    void create_directory_with_file(const std::string& dir_name)
    {
        if (!std::filesystem::exists(dir_name)) {
            std::filesystem::create_directory(dir_name);
        }
    }

    void save_renderer_api_config(int api)
    {
        create_directory_with_file("bin");

        std::ofstream file(main_app_configuration_file_path, std::ios::out);

        if (file.is_open()) {
            file << "Renderer : " << api << '\n';
            file.close();
        }
    }

    std::string get_api()
    {
        std::ifstream file(main_app_configuration_file_path);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << main_app_configuration_file_path << '\n';
            return "0";
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.rfind("Renderer : ", 0) == 0) { // Check if line starts with "Renderer="
                return line.substr(11); // Extract value after '='
            }
        }

        return "0";
    }
}