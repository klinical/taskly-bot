#include <dpp/dpp.h>
#include <utility>
#include "spdlog/logger.h"
#include "spdlog/async.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

const std::string    BOT_TOKEN    = "NTkyMTQxMzE3MDkwNDQzNDEy.GTiGy9.Apii6b9f4lsNCebLNRWuZGFff43T9ibKr6w34I";
const dpp::snowflake MY_GUILD_ID  =  598649811964788755;

class todo_item {
public:
    std::string owner;
    std::string message;

    // Take in string params and move ownership to member vars
    todo_item(const std::string&  owner_, const std::string&  message_)
    : owner {std::move( owner_ )}, message {std::move( message_ )} { }
};

class todo_list {
    std::vector<todo_item> items;

public:
    // Default constructor
    todo_list() = default;

    void add_item(todo_item item) { items.push_back(item); }

    std::vector<todo_item> get_items() { return items; }
};

void create_command(dpp::cluster& bot, const dpp::slashcommand& cmd) {
    bot.guild_command_create(cmd, MY_GUILD_ID);
}

int main() {
    dpp::cluster bot(BOT_TOKEN);
    todo_list todo_list;
    const std::string log_name = "mybot.log";

    /* Set up spdlog logger */
    std::shared_ptr<spdlog::logger> log;
    spdlog::init_thread_pool(8192, 2);
    std::vector<spdlog::sink_ptr> sinks;
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    auto rotating = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_name, 1024 * 1024 * 5, 10);
    sinks.push_back(stdout_sink);
    sinks.push_back(rotating);
    log = std::make_shared<spdlog::async_logger>("logs", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    spdlog::register_logger(log);
    log->set_pattern("%^%Y-%m-%d %H:%M:%S.%e [%L] [th#%t]%$ : %v");
    log->set_level(spdlog::level::level_enum::debug);

    bot.on_log([&log](const dpp::log_t& event) {
        std::cout << event.message;
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

        if (cmd == "list") {
            std::string response {};

            // Build up response string
            for (todo_item& item : todo_list.get_items()) {
                response += "owner: " + item.owner + " message: " + item.message + '\n';
            }

            bot.log( dpp::ll_warning, "Logged!");

            event.reply(response);
        } else if (cmd == "add") {
            const std::string& cmd_sender = event.command.member.nickname;
            const std::string& cmd_msg = std::get<std::string>(event.get_parameter("message"));

            // Create new item
            todo_item new_item { cmd_sender, cmd_msg };

            // Add it to the list
            todo_list.add_item(new_item);
            event.reply("Added message");
        }
    });

    // Once ready, if first start, create the commands
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand add_to_list("add", "add a message to the list", bot.me.id);
            add_to_list.add_option(
                    dpp::command_option(dpp::co_string, "message", "Your message")
                    );

            dpp::slashcommand get_list("list", "gets the list", bot.me.id);

            create_command(bot, add_to_list);
            create_command(bot, get_list);
        }
    });

    bot.start(false);
}