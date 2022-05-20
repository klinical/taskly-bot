
#include "spdlog/spdlog.h"
#include "bot/DiscordBot.h"

int main(int argc, char* argv[])
{
    try
    {
        // Logger init
        spdlog::flush_every(std::chrono::seconds(5));

        // Init bot
        DiscordBot::LaunchMode mode{ DiscordBot::LaunchMode::standard };
        DiscordBot discord_bot { BotConfig::from_file("../bot.cfg") };

        if (argc > 1)
        {
            std::cout << argv[0] << '\n';
            std::cout << argv[1] << '\n';
            std::string_view init_mode{ argv[1] };

            if (init_mode == "--load-cmds")
            {
                mode = DiscordBot::LaunchMode::fresh;
                discord_bot.register_commands();
            }
        }

        discord_bot.start(mode);
    }
    catch(const std::exception& ex)
    {
        std::cerr << "[ERROR] Unhandled std library exception" << '\n';
        std::cerr << ex.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "[ERROR] Unhandled exception @main.cpp>main()" << '\n';
    }

    return 0;
}