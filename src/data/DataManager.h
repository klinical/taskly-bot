//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_DATAMANAGER_H
#define DISCORD_BOT_DATAMANAGER_H

#include <fstream>
#include <map>
#include <list>
#include <string>
#include <json.hpp>
#include <utility>
#include "logger.h"

using nlohmann::json;

class DataManager {
    /**
     * Key: Name of the list
     * Value: a linked list of the list's items
     */
public:
    typedef std::map<std::string, std::list<std::string>> ListMap;

private:
    std::fstream m_fstream;
    std::string m_file_loc;
    ListMap m_list{ };

    std::shared_ptr<spdlog::logger> m_logger;

public:
    void load_data();
    void remove_list_item(std::string key, std::string val);
    ListMap* full_list();

    explicit DataManager(const std::string& file_loc, std::shared_ptr<spdlog::logger> logger);
};


#endif //DISCORD_BOT_DATAMANAGER_H
