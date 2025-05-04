#ifndef KONKR_MAP_FILE_HPP
#define KONKR_MAP_FILE_HPP

#include <string>

#include "Konkr/Hex/HexContainer.hpp"

namespace map_file
{
    HexContainer read_map(const std::string& map_name);
    std::vector<std::string> find_map_files(const std::string& directory);
    void save_map(const HexContainer& map, const std::string& map_name);
}

#endif // KONKR_MAP_FILE_HPP