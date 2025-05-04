#include "Konkr/IO/MapFile.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <ranges>

#include "Engine/Utils/Logs.hpp"
#include "Konkr/Models/Buildings/Castle.hpp"
#include "Konkr/Models/Buildings/Tower.hpp"
#include "Konkr/Models/Units/Knight.hpp"
#include "Konkr/Models/Units/Soldier.hpp"
#include "Konkr/Models/Units/Villager.hpp"

namespace
{
    std::vector<std::string> split(std::string str, const std::string& delimiter)
    {
        std::vector<std::string> tokens;
        size_t pos;
        while ((pos = str.find(delimiter)) != std::string::npos)
        {
            std::string token = str.substr(0, pos);
            if (!token.empty() && token.back() == '\r')
                token.pop_back();
            tokens.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        if (!str.empty() && str.back() == '\r')
            str.pop_back();
        tokens.push_back(str);
        return tokens;
    }

    HexType string_to_hex_type(const std::string& type_str)
    {
        if (type_str == "D")
            return HexType::Decoration;
        if (type_str == "T")
            return HexType::Territory;
        logs::error("Unknown hextype {} in map", type_str);
        return HexType::Unknown;
    }

    Entity::SP string_to_entity(const std::string& decoration_str)
    {
        if (decoration_str == "V")
            return std::make_shared<Villager>();
        if (decoration_str == "C")
            return std::make_shared<Castle>();
        if (decoration_str == "T")
            return std::make_shared<Tower>();
        if (decoration_str == "S")
            return std::make_shared<Soldier>();
        if (decoration_str == "K")
            return std::make_shared<Knight>();
        return nullptr;
    }

    std::string hex_decoration_to_string(const HexEntity decoration)
    {
        switch (decoration)
        {
        case HexEntity::Villager: 
            return "V";
        case HexEntity::Castle:   
            return "C";
        case HexEntity::Tower:    
            return "T";
        case HexEntity::Soldier:  
            return "S";
        case HexEntity::Knight:
            return "K";
        case HexEntity::None:
        default:                     
            return "X"; 
        }
    }

    std::string hex_type_to_string(const HexType type)
    {
        switch (type)
        {
        case HexType::Decoration:
            return "D";
        case HexType::Territory:
            return "T";
        case HexType::Unknown:
        default:
            return "X";
        }
    }
}

HexContainer map_file::read_map(const std::string& map_name)
{
    const std::string file_path = constants::path_maps + map_name + ".map";
    std::ifstream file{ file_path };
    if (!file.is_open())
    {
        logs::error("Failed to open map file: {}", file_path);
        return HexContainer{};
    }

    HexContainer container{};
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = split(line, ";");
        if (tokens.size() != 6)
        {
            logs::error("Invalid map line: {}", line);
            return container;
        }
        const int q = std::stoi(tokens[0]);
        const int r = std::stoi(tokens[1]);
        const int s = std::stoi(tokens[2]);
        const int player = std::stoi(tokens[3]);
        const HexType type = string_to_hex_type(tokens[4]);
        const Entity::SP state = string_to_entity(tokens[5]);
        if (q + r + s != 0)
        {
            logs::error("Invalid hex coordinates: {}, {}, {}", q, r, s);
            return container;
        }
        container.add_hex(HexTile(q, r, s, type, state, player));
    }
    file.close();
    return container;
}

std::vector<std::string> map_file::find_map_files(const std::string& directory)
{
    std::vector<std::string> map_files;

    try
    {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
            if (entry.is_regular_file() && entry.path().extension() == ".map")
                map_files.push_back(entry.path().stem().string());
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        logs::error("Error accessing directory {}: {}", directory, e.what());
        return map_files;
    }
            
    return map_files;
}

void map_file::save_map(const HexContainer& map, const std::string& map_name)
{
    const std::string file_path = constants::path_maps + map_name + ".map";
    std::ofstream file{ file_path };
    if (!file.is_open())
    {
        logs::error("Failed to open map file for writing: {}", file_path);
        return;
    }
    for (const HexTile& hex : map | std::views::values)
    {
        static constexpr auto format_coord = [](const int coord) -> std::string
        {
            return coord >= 0 ? '+' + std::to_string(coord) : std::to_string(coord);
        };

        file << format_coord(hex.q()) << ";"
            << format_coord(hex.r()) << ";"
            << format_coord(hex.s()) << ";"
            << hex.get_player() << ";"
            << hex_type_to_string(hex.get_type()) << ";"
            << hex_decoration_to_string(hex.get_decoration()) << "\n";
    }
    file.close();
}
