//
// Created by zach on 5/13/22.
//

#ifndef DISCORD_BOT_BOT_CONFIG_H
#define DISCORD_BOT_BOT_CONFIG_H

#include <string>
#include <utility>
#include "dpp/snowflake.h"

class bot_config {
private:
    std::string bot_token;
    dpp::snowflake guild_id;
public:
    [[nodiscard]]
    const std::string &getBotToken() const;

    [[nodiscard]]
    dpp::snowflake getGuildId() const;

    // Move/take ownership of bot token
    bot_config(std::string m_token, dpp::snowflake m_guild)
        : bot_token { std::move(m_token) }, guild_id {m_guild} { }

public:
    static bot_config from_flat_file(const char* path);
};

#endif //DISCORD_BOT_BOT_CONFIG_H
