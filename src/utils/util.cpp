//
// Created by zach on 5/20/22.
//

#include <fstream>
#include <iostream>
#include "util.h"
#include "dpp/nlohmann/json.hpp"

namespace util
{
    void mk_backup(std::string&& file_loc)
    {
        std::ifstream src{ file_loc, std::ios::binary };
        std::ofstream dst{ file_loc + ".bk", std::ios::binary };

        dst << src.rdbuf();
    }

    template <typename T>
    void print_vec(std::vector<T>& v)
    {
        int i{ };
        for (auto& item : v)
        {
            std::cout << i << ": " << item << '\n';
            i++;
        }
    }

    void clear_line(long int pos, std::fstream& stream, std::size_t end)
    {
        // Clear line from pos
        stream.seekg(pos);
        for (int i{}; i < end; i++)
            stream << " ";

        // Reset back to pos
        stream.seekg(pos);
    }

    void remove_item_from_list(std::pair<long int, long int> location, int idx)
    {
        // mk_backup("../data.json");
        std::fstream stream("../data.json.bk");
        // Move file pointer to pos of first char of starting line of target object in file
        stream.seekg(location.first);

        // Read a line and reset pointer back to beginning
        std::string line;
        std::getline(stream, line);

        // Parse line as JSON
        std::stringstream ss;
        ss << '{' << line << '}';
        nlohmann::json j{ nlohmann::json::parse(ss.str()) };

        // Collect list elements from parsed JSON
        std::vector<std::string> items = j[0].at("items");

        // Clear the current line
        clear_line(location.first, stream, line.size());

        // Remove target element
        items.erase(items.begin() + idx);

        // Write updated JSON to line
        stream << "    " << R"("items")" << ": [";
        int i{ };
        for (auto& item : items)
        {
            stream << '"' << item << '"';

            if (i != items.size()-1)
            {
                stream << ',';
            }
            else
            {
                stream << ']';
            }
            i++;
        }
    }

    std::pair<long int, long int> find_item_in_list()
    {
        nlohmann::json j;
        std::fstream fstream;
        fstream.open("../data.json");

        std::string list_name{ "list" };

        std::string search{ R"("name": ")" + list_name + "\"" };

        // first = line number
        // second = object number
        auto res_pair{ std::pair<long int, long int>(-1, -1) };
        std::string line;
        while (std::getline(fstream, line))
        {
            // Skip the  enclosing array chars
            if (line.at(0) == '[' || line.at(0) == ']')
                continue;

            // Skip end of object tag
            if (line.at(2) == '}')
                continue;

            // Opening of new object
            else if (line.at(2) == '{')
                res_pair.second++;

            else
                if (line.find(search, 0) != std::string::npos)
                {
                    res_pair.first = fstream.tellg();
                    reset_file_ptr(fstream);
                    return res_pair;
                }
        }

        // Line was not found
        return res_pair;
    }

    void reset_file_ptr(std::fstream& stream)
    {
        stream.close();
        stream.seekg(0);
    }
}
