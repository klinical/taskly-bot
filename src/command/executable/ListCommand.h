//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_LISTCOMMAND_H
#define DISCORD_BOT_LISTCOMMAND_H

#include "registry/CommandRegistrarEntry.h"
#include "CommandExecutable.h"

class ListCommand: public CommandExecutable {
public:
    std::vector<dpp::command_option> options{};

    void execute(const ExecutionContext& ctx) override
    {
        // todo, actually use data
        ctx.m_event->reply(ctx.m_data);
    }

    ListCommand()
    {
        // add all options here
        options.emplace_back( dpp::co_string, "message", "hi" );
    }
};


#endif //DISCORD_BOT_LISTCOMMAND_H
