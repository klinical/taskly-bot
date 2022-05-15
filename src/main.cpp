
#include "spdlog/spdlog.h"
#include "bot/DiscordBot.h"

int main() {
    // Logger init
    // todo, allow multiple loggers, log level, etc
    spdlog::flush_every(std::chrono::seconds(5));

    // Init state
    DiscordBot discord_bot { BotConfig::from_file("../bot.cfg") };
    discord_bot.start();

    return 0;
}