//
// Created by zach on 5/13/22.
//

#include "processor.h"

void processor::create_command(dpp::cluster &bot, const dpp::slashcommand& cmd, dpp::snowflake guild_id) {
    bot.guild_command_create(cmd, guild_id);
}

processor::processor(const bot_config& config, todo_list& list)
        : m_cluster { config.getBotToken() }, m_list { list } {
    m_cluster.on_log([](const dpp::log_t& event) {
        logger::logger_type logger = logger::get_instance();

        switch (event.severity) {
            // Must dereference m_spdlg
            case dpp::ll_critical:
                logger->critical(event.message);
                break;
            case dpp::ll_error:
                logger->error("{}", event.message);
                break;
            case dpp::ll_warning:
                logger->warn("{}", event.message);
                break;
            default:
                logger->info("{}", event.message);
                break;
        }
    });

    // On interaction
    m_cluster.on_interaction_create([this](const dpp::interaction_create_t& event) {
        std::string cmd = event.command.get_command_name();

        m_cluster.log(dpp::ll_info, "Received command: " + cmd);

        if (cmd == "list") {
            event.reply(m_list.str());
        } else if (cmd == "add") {
            const std::string& cmd_sender = event.command.member.nickname;
            const auto& cmd_msg = std::get<std::string>(event.get_parameter("message"));

            // Create new item
            todo_item new_item { cmd_sender, cmd_msg };
            m_data_writer.write_new_todo_item({ cmd_sender, cmd_msg });

            // Add it to the list in memory
            m_list.add_item(new_item);
            event.reply("Added message");
        }
    });

    // Once ready, if first start, create the commands
    m_cluster.on_ready([this](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand add_to_list("add", "add a message to the list", m_cluster.me.id);
            add_to_list.add_option(
                    dpp::command_option(dpp::co_string, "message", "Your message")
            );

            dpp::slashcommand get_list("list", "gets the list", m_cluster.me.id);

            create_command(bot, add_to_list, bot_config.guild_id);
            create_command(bot, get_list, bot_config.guild_id);

            m_cluster.log(dpp::ll_info, "Registered commands.");
        }

        m_cluster.log(dpp::ll_info, "Bot ready.");
        m_cluster.log(dpp::ll_info, "Took " + std::to_string(t.elapsed()) + " seconds.");
    });

    m_cluster.start(false);
}