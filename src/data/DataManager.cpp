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

void DataManager::remove_list_item(std::string key, int idx)
{
    auto object_index_number{ util::find_item_in_list() };

    // Object was found?
    if (object_index_number.first >= 0)
    {
        util::remove_item_from_list(object_index_number, idx);
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
        auto item_list{ std::make_unique<std::list<std::string>>() };
        for(auto [key, value] : file_list.items())
        {
            item_list->emplace_back(value);
        }

        m_list.insert({ std::string(list_key), std::move(item_list) } );
    }
}
