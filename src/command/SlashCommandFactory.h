//
// Created by zach on 5/17/22.
//

#ifndef DISCORD_BOT_SLASHCOMMANDFACTORY_H
#define DISCORD_BOT_SLASHCOMMANDFACTORY_H


#include <string>
#include <vector>
#include "dpp/appcommand.h"

class SlashCommandFactory {
private:
    dpp::snowflake m_guild;

public:
    explicit SlashCommandFactory(dpp::snowflake guild) : m_guild{ guild }
    { }

    dpp::slashcommand build_command(const std::string& title, const std::string& desc, std::vector<dpp::command_option>* options) const
    {
        dpp::slashcommand cmd { title, desc, m_guild };

        if (options)
            for (auto& option : *options) {
                cmd.add_option(option);
            }

        return cmd;
    }
};


#endif //DISCORD_BOT_SLASHCOMMANDFACTORY_H
