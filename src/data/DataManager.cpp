//
// Created by zach on 5/14/22.
//

#include <iostream>
#include <utility>
#include "DataManager.h"
#include "util.h"

/**
 * Open the fstream in read & write mode
 * @param file_loc the location of the file
 */
DataManager::DataManager(const std::string& file_loc, std::shared_ptr<spdlog::logger> logger)
    :   m_fstream(file_loc),
        m_logger{std::move( logger )}
{
    // Set the flags to act as thrown exceptions from fstream
//    m_fstream.exceptions(std::fstream::failbit | std::fstream::badbit);
}

DataManager::ListMap* DataManager::full_list()
{
    return &m_list;
}

void DataManager::remove_list_item(std::string key, std::string val)
{
    auto object_index_number{ util::find_item_in_list() };

    // Object was found?
    if (object_index_number.first >= 0)
    {
        m_fstream.seekg(object_index_number.first);
    }
}

void DataManager::load_data()
{
    // Create file if not exists
    m_fstream.open(m_file_loc.c_str(), std::ios::out);
    // Open file
    m_fstream.open(m_file_loc.c_str());

    json j;
    m_fstream >> j;

    for (auto& [list_key, file_list] : j.items())
    {
        std::list<std::string> item_list{ };

        for(auto& [key, value] : file_list.items())
        {
            auto _item = value.get<std::string>();
            m_logger->info("Read item from key " + list_key + " value " + _item);
            file_list.emplace_back(value);
        }

        m_list.insert({ list_key, std::move(item_list) } );
    }
}
