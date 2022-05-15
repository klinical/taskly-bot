//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_COMMANDREGISTRARENTRY_H
#define DISCORD_BOT_COMMANDREGISTRARENTRY_H


#include <utility>

#include "dpp/dispatcher.h"
#include "../executable/ExecutionContext.h"
#include "executable/CommandExecutable.h"

class CommandRegistrarEntry {

public:
    dpp::slashcommand slashcommand;
    CommandExecutable executable;

    CommandRegistrarEntry(const std::string& name, const std::string& desc, dpp::snowflake id, const CommandExecutable&  ex)
        : slashcommand{ name, desc, id }, executable{std::move( ex )}
   {}
};

#endif //DISCORD_BOT_COMMANDREGISTRARENTRY_H
