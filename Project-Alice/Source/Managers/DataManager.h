#pragma once
#include <pch.h>
#include <Overlay/Overlay.h>
#include <Globals/API.h>

namespace DataManager
{
    inline std::string main_app_configuration_file_path = "bin/configuration.ini";

    void create_directory_with_file(const std::string& dir_name);
    void save_renderer_api_config(int api);
    std::string get_api();
}