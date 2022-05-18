//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_COMMANDREGISTRAR_H
#define DISCORD_BOT_COMMANDREGISTRAR_H


#include <string>
#include <unordered_map>
#include "Command.h"

class CommandRegistrar {
public:
    typedef std::unordered_map<std::string, Command> CommandMap;

private:
    dpp::snowflake guild_id{3};
    dpp::snowflake m_app_id;
    CommandMap commands;

public:
    CommandRegistrar& set_app_id(dpp::snowflake id)
    {
        m_app_id = id;

        return *this;
    }

    Command get_command(const std::string& key)
    {
        return commands.at(key);
    }

    // Seems to be a memory issue around here
    CommandRegistrar& add_command(Command command)
    {
        commands.insert({command.m_cmd->name, command});

        return *this;
    }

    ~CommandRegistrar()
    {
        // Free the dynamically allocated memory for all the commands
        for (const std::pair<const std::basic_string<char>, Command>& cmd : commands) {
            delete cmd.second.m_cmd;
            delete cmd.second.m_executor;
        }
    }

    CommandRegistrar& add_guild(dpp::snowflake id)
    {
        guild_id = id;

        return *this;
    }

    void register_commands(dpp::cluster& cluster)
    {
        for (auto const& [_, cmd] : commands)
        {
            cluster.guild_command_create(*(cmd.m_cmd), guild_id);
        }
    }

};


#endif //DISCORD_BOT_COMMANDREGISTRAR_H
