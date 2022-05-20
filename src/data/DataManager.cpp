//
// Created by zach on 5/14/22.
//

#include <iostream>
#include "DataManager.h"

/**
 * Open the fstream in read & write mode
 * @param file_loc the location of the file
 */
DataManager::DataManager(std::string file_loc)
    :   m_file_loc{ std::move(file_loc) }
{
    // Set the flags to act as thrown exceptions from fstream
    m_fstream.exceptions( std::fstream::failbit | std::fstream::badbit );
}

void DataManager::load_data() {
    m_fstream.open(m_file_loc, std::ios::in | std::ios::out);

    json j;
    m_fstream >> j;

    std::list<std::string> list{ };
    for ( auto& [key, value] : j.items())
    {
        list.emplace_back(value);

        m_list.insert({ key.c_str(), list } );
    }
}
