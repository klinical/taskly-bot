//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_COMMANDREGISTRAR_H
#define DISCORD_BOT_COMMANDREGISTRAR_H


#include <string>
#include <unordered_map>
#include "CommandRegistrarEntry.h"

class CommandRegistrar {
public:
    typedef std::unordered_map<std::string, CommandRegistrarEntry> CommandMap;

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

    CommandRegistrarEntry get_command(const std::string& key)
    {
        return commands.at(key);
    }

    // Seems to be a memory issue around here
    CommandRegistrar& add_command(const std::string& name, std::string desc, const CommandExecutable& executable)
    {
        name.c_str();
        CommandRegistrarEntry new_cmd { name, desc, m_app_id, executable };

        for (dpp::command_option option : executable.options)
        {
            new_cmd.slashcommand.add_option(option);
        }

        commands.insert({ name, new_cmd });

        return *this;
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
            cluster.guild_command_create(cmd.slashcommand, guild_id);
        }
    }

};


#endif //DISCORD_BOT_COMMANDREGISTRAR_H
