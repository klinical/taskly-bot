//
// Created by zach on 5/14/22.
//

#include "DiscordBot.h"

void DiscordBot::register_commands() {
    // Register the commands
    SlashCommandFactory cmd_factory{ };
    cmd_factory.app_id(m_cluster.me.id);

    auto list_cmd = new ListCommand();
    auto add_cmd = new AddItemCommand();
    auto add_cmd_opts = {
            dpp::command_option{
                    dpp::co_string,
                    "list",
                    "list name to add to"
            }
    };

    command_registrar
            .set_app_id(m_cluster.me.id)
            .add_guild(m_config.get_guild_id())
            .add_command(
                    cmd_factory
                            .executor(list_cmd)
                            .title("list")
                            .desc("list all items")
                            .build()
            )
            .add_command(
                    cmd_factory
                            .executor(add_cmd)
                            .title("add")
                            .desc("add a new item")
                            .options(add_cmd_opts)
                            .build()
            )
            .register_commands(m_cluster);

    m_logger->info("Registered commands.");
}

DiscordBot::DiscordBot(BotConfig cfg)
    :   m_config{ std::move( cfg ) },
        m_cluster{ m_config.get_token() }
{
    m_cluster.on_log([this](const dpp::log_t& event) {
        std::cout << event.message << '\n';
        switch (event.severity) {
            case dpp::ll_critical:
                m_logger->critical(event.message);
                break;
            case dpp::ll_error:
                 m_logger->error("{}", event.message);
                 break;
            case dpp::ll_warning:m_logger->warn("{}", event.message);break;
            default:
                m_logger->info("{}", event.message);
                break;
        }
    });

    m_cluster.on_interaction_create([this](const dpp::interaction_create_t& event) {
        std::string command_name = event.command.get_command_name();

        m_cluster.log(dpp::ll_info, command_name);
        // Look up command in registrar
        Command command = command_registrar.get_command(command_name);

        // Build ctx
        ExecutionContextBuilder eb;
        ExecutionContext ctx {
                eb.set_event(event)
                        .set_logger(m_logger)
                        .set_cluster(m_cluster)
                        .set_writer(m_data)
                        .build()
        };

        command.m_executor->execute(ctx);
    });

    m_cluster.on_ready([this](const dpp::ready_t& event) {
       if (dpp::run_once<struct register_bot_commands>()) {
           m_logger->info("Bot started successfully.");
       }
    });

    try
    {
        _m_data.load_data();
    }
    catch(std::fstream::failure& ex)
    {
        m_cluster.log(dpp::ll_critical, "Exception reading data file");
        m_cluster.log(dpp::ll_critical, ex.what());
    }
    catch(...)
    {
        m_cluster.log(dpp::ll_critical, "Unexpected exception in loading data.");
    }
}

void DiscordBot::start(DiscordBot::LaunchMode mode) {
    if (mode == LaunchMode::fresh)
        register_commands();

    m_cluster.start(false);
}