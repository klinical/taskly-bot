//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_BOTCONFIG_H
#define DISCORD_BOT_BOTCONFIG_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include "dpp/snowflake.h"

class BotConfig {
    std::string bot_token{ };
    dpp::snowflake guild_id{ };

public:
    BotConfig() = default;
    BotConfig(std::string bot_token, dpp::snowflake guild_id)
        : bot_token{ std::move(bot_token) }, guild_id{ guild_id }
    {}

    static BotConfig from_file(const char* file_path)
    {
        std::ifstream file;
        file.open(file_path);

        std::string bot_token;
        std::string guild_id_str;
        std::getline(file, bot_token, ',');
        std::getline(file, guild_id_str, '\n');

        // Convert the guild id string buffer to an uint64_t using an istringstream
        dpp::snowflake guild_id;
        std::istringstream iss(guild_id_str);
        iss >> guild_id;

        return BotConfig { bot_token, guild_id };
    }

    std::string get_token()
    {
        return this->bot_token;
    }

    [[nodiscard]]
    dpp::snowflake get_guild_id() const
    {
        return guild_id;
    }

};


#endif //DISCORD_BOT_BOTCONFIG_H
