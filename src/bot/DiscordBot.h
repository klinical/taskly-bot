//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_DISCORDBOT_H
#define DISCORD_BOT_DISCORDBOT_H

#include <utility>

#include "dpp/once.h"
#include "dpp/cluster.h"

#include "BotConfig.h"
#include "logger.h"
#include "registry/CommandRegistrar.h"
#include "executable/ExecutionContextBuilder.h"
#include "executable/ListCommand.h"
#include "executable/AddItemCommand.h"
#include "SlashCommandFactory.h"
#include "DataManager.h"

class DiscordBot {
public:
    enum LaunchMode {
        standard,
        fresh,
        test
    };

private:
    BotConfig m_config;
    std::unique_ptr<dpp::cluster> m_cluster;
    LaunchMode m_launch_mode;

    CommandRegistrar command_registrar;

    std::shared_ptr<spdlog::logger> m_logger{ logger::get_instance() };
    std::unique_ptr<DataManager> m_data_manager;

public:
    explicit DiscordBot(BotConfig cfg, LaunchMode mode);

    void start();
    void register_commands();
};


#endif //DISCORD_BOT_DISCORDBOT_H
