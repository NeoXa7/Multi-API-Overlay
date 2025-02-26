#pragma once
#include <pch.h>
#include <Overlay/Overlay.h>
#include <Globals/API.h>

namespace DataManager
{
    void create_directory_with_file(const std::string& dir_name, const std::string& file_name);
    void save_renderer_api_config(std::string api);
    std::string get_api();
}