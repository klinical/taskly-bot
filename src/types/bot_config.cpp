//
// Created by zach on 5/13/22.
//

#include "bot_config.h"

#include <iostream>
#include <fstream>
#include <sstream>

bot_config bot_config::from_flat_file(const char* path) {
    std::ifstream file;
    file.open(path);

    std::string bot_token;
    std::string guild_id_str;
    std::getline(file, bot_token, ',');
    std::getline(file, guild_id_str, '\n');

    std::cout << "Loaded bot.cfg with values "
        << bot_token
        << " , "
        << guild_id_str
        << '\n';

    // Convert the guild id string buffer to an uint64_t using an istringstream
    dpp::snowflake guild_id;
    std::istringstream iss(guild_id_str);
    iss >> guild_id;

    bot_config config{bot_token, guild_id};

    return config;
}

const std::string &bot_config::getBotToken() const {
    return bot_token;
}

dpp::snowflake bot_config::getGuildId() const {
    return guild_id;
}
