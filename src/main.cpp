
#include "spdlog/spdlog.h"
#include "bot/DiscordBot.h"
#include "util.h"

int main(int argc, char* argv[])
{
    try
    {
        // Logger init
        spdlog::flush_every(std::chrono::seconds(5));

        // Init bot
        DiscordBot::LaunchMode mode{ DiscordBot::LaunchMode::standard };

        if (argc > 1)
        {
            std::string_view init_mode{ argv[1] };

            if (init_mode == "--load-cmds")
            {
                mode = DiscordBot::LaunchMode::fresh;
            }
            else if (init_mode == "--run-tests")
            {
                mode = DiscordBot::LaunchMode::test;

                auto pos = util::find_item_in_list();
                util::remove_item_from_list(pos, 0);

                if (util::find_item_in_list().first < 0)
                {
                    throw std::exception();
                }
                else
                {
                    std::cout << "Tests passed successfully." << std::endl;
                }
            }
        }

        if (mode != DiscordBot::LaunchMode::test)
        {
            DiscordBot discord_bot { BotConfig::from_file("../bot.cfg"), mode };
            discord_bot.start();
        }
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