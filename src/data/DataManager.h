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

using nlohmann::json;

class DataManager {
    /**
     * Key: Name of the list
     * Value: a linked list of the list's items
     */
public:
    typedef std::map<const char*, std::list<std::string>> ListMap;

private:
    std::fstream m_fstream;
    std::string m_file_loc;
    ListMap m_list{ };

public:
    void load_data();

    explicit DataManager(std::string file_loc);
};


#endif //DISCORD_BOT_DATAMANAGER_H
