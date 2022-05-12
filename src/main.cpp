#include "todo/todo_list.h"

#include <dpp/dpp.h>
#include "spdlog/logger.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <string>

const std::string LIST_FILE = "todo_data";

void create_command(dpp::cluster& bot, const dpp::slashcommand& cmd, int guild_id) {
    bot.guild_command_create(cmd, guild_id);
}

struct bot_config {
    std::string bot_token;
    dpp::snowflake guild_id; // 64 bit unsigned int
};

todo_list read_list_from_file() {
    std::string owner_buffer {};
    std::string message_buffer {};
    todo_list list;

    std::ifstream list_file;
    list_file.open(LIST_FILE);

    if (list_file.is_open()) {
        // Work up until comma (owner), then to semicolon (message) and loop
        while (std::getline(list_file, owner_buffer, ':') &&
        std::getline(list_file, message_buffer, ';')) {
            todo_item new_item { owner_buffer, message_buffer };

            std::cout << "Created item: " << new_item.serialize() << '\n';
            list.add_item(new_item);
        }
    } else {
        std::cout << "Failed to open file." << '\n';
    }

    return list;
}

bot_config load_bot_config() {
    std::ifstream file;
    file.open("../bot.cfg");

    std::string bot_token;
    std::string guild_id_str;
    std::getline(file, bot_token, ',');
    std::getline(file, guild_id_str, '\n');

    std::cout << "Loaded bot.cfg with values " << bot_token << " , " << guild_id_str << '\n';

    // Convert the guild id string buffer to an uint64_t using an istringstream
    dpp::snowflake guild_id;
    std::istringstream iss(guild_id_str);
    iss >> guild_id;

    bot_config config { bot_token, guild_id };

    return config;
}

int main() {
    // Logger init
    std::shared_ptr<spdlog::logger> log = spdlog::basic_logger_mt("basic_logger", "log/bot.log");
    spdlog::flush_every(std::chrono::seconds(5));

    // Bot init
    bot_config bot_config { load_bot_config() };
    dpp::cluster bot(bot_config.bot_token);
    todo_list todo_list { read_list_from_file() };

    bot.on_log([&log](const dpp::log_t& event) {
        std::cout << "[" << event.severity << "] " << event.message << '\n';

        switch (event.severity) {
            case dpp::ll_critical:
                log->critical((event.message));
                break;
            case dpp::ll_error:
                log->error("{}", event.message);
                break;
            default:
                log->info("{}", event.message);
                break;
        }
    });

    // On interaction
    bot.on_interaction_create([&todo_list, &bot](const dpp::interaction_create_t& event) {
        std::string cmd = event.command.get_command_name();

        bot.log(dpp::ll_info, "Received command: " + cmd);

        if (cmd == "list") {
            std::string response {};

            // Build up response string
            for (todo_item& item : todo_list.get_items()) {
                response += "owner: " + item.owner + " message: " + item.message + '\n';
            }

            event.reply(response);
        } else if (cmd == "add") {
            const std::string& cmd_sender = event.command.member.nickname;
            const auto& cmd_msg = std::get<std::string>(event.get_parameter("message"));

            // Create new item
            todo_item new_item { cmd_sender, cmd_msg };

            // Open file for writing in app(end) mode
            std::ofstream todo_file;
            todo_file.open(LIST_FILE, std::ofstream::app);

            todo_file << new_item.serialize();
            todo_file.close();

            // Add it to the list in memory
            todo_list.add_item(new_item);
            event.reply("Added message");
            bot.log(dpp::ll_info, "New item saved successfully.");
        }
    });

    // Once ready, if first start, create the commands
    bot.on_ready([&bot, &bot_config](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand add_to_list("add", "add a message to the list", bot.me.id);
            add_to_list.add_option(
                    dpp::command_option(dpp::co_string, "message", "Your message")
                    );

            dpp::slashcommand get_list("list", "gets the list", bot.me.id);

            create_command(bot, add_to_list, bot_config.guild_id);
            create_command(bot, get_list, bot_config.guild_id);

            bot.log(dpp::ll_info, "Registered commands.");
        }

        bot.log(dpp::ll_info, "Bot ready.");
    });

    bot.start(false);

    return 0;
}