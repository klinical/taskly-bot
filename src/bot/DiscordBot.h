//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_DISCORDBOT_H
#define DISCORD_BOT_DISCORDBOT_H

#include <utility>

#include "BotConfig.h"
#include "dpp/cluster.h"
#include "logger.h"
#include "registry/CommandRegistrar.h"
#include "executable/ExecutionContextBuilder.h"
#include "executable/ListCommand.h"
#include "executable/AddItemCommand.h"
#include "dpp/once.h"
#include "SlashCommandFactory.h"
#include "DataManager.h"

class DiscordBot {
public:
    enum LaunchMode {
        standard,
        fresh,
    };

private:
    BotConfig m_config;
    dpp::cluster m_cluster;

    CommandRegistrar command_registrar;
    std::shared_ptr<spdlog::logger> m_logger{ logger::get_instance() };
    DataManager _m_data{ "data_file" };
    std::string m_data{};

public:
    explicit DiscordBot(BotConfig cfg);

    void start(LaunchMode mode);
    void register_commands();
};


#endif //DISCORD_BOT_DISCORDBOT_H
