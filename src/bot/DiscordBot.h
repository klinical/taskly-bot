//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_DISCORDBOT_H
#define DISCORD_BOT_DISCORDBOT_H

#include <utility>

#include "BotConfig.h"
#include "dpp/cluster.h"
#include "registry/CommandRegistrarEntry.h"
#include "logger.h"
#include "registry/CommandRegistrar.h"
#include "executable/ExecutionContextBuilder.h"
#include "executable/ListCommand.h"
#include "executable/AddItemCommand.h"
#include "dpp/once.h"

class DiscordBot {
    BotConfig m_config;
    dpp::cluster m_cluster;

    CommandRegistrar command_registrar;
    std::shared_ptr<spdlog::logger> m_logger{ logger::get_instance() };
    std::string m_data{};

public:
    void start()
    {
        m_cluster.start(false);
    }

    explicit DiscordBot(BotConfig cfg): m_config{std::move( cfg )}, m_cluster{ m_config.get_token() }
    {
        m_cluster.on_log([this](const dpp::log_t& event)
        {
            std::cout << event.message << '\n';
            switch (event.severity) {
                case dpp::ll_critical:
                    m_logger->critical(event.message);
                    break;
                case dpp::ll_error:
                    m_logger->error("{}", event.message);
                    break;
                case dpp::ll_warning:
                    m_logger->warn("{}", event.message);
                    break;
                default:
                    m_logger->info("{}", event.message);
                    break;
            }
        });
        m_cluster.on_interaction_create([this](const dpp::interaction_create_t& event)
        {
            m_cluster.log(dpp::ll_info, event.command.get_command_name());
            CommandRegistrarEntry command = command_registrar.get_command(event.command.get_command_name());

            ExecutionContextBuilder eb;
            ExecutionContext ctx {
                eb.event(event)
                .logger(m_logger)
                .cluster(m_cluster)
                .data(m_data)
                .build()
            };

            command.executable.execute(ctx);
        });

        m_cluster.on_ready([this](const dpp::ready_t& event)
        {
            if (dpp::run_once<struct register_bot_commands>()) {
                // Register the commands
                // memory issue origin
                // likely *Command objects are being released at the end of add_component
                // and having their mem. freed
                command_registrar
                    .set_app_id(m_cluster.me.id)
                    .add_guild(m_config.get_guild_id())
                    .add_command("list", "test", ListCommand())
                    .add_command("add","test",AddItemCommand())
                    .register_commands(m_cluster);
                m_cluster.log(dpp::ll_info, "test");
            }
        });
    }
};


#endif //DISCORD_BOT_DISCORDBOT_H