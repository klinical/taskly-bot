//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_ADDITEMCOMMAND_H
#define DISCORD_BOT_ADDITEMCOMMAND_H

#include "ExecutionContext.h"
#include "CommandExecutable.h"

class AddItemCommand: public CommandExecutable {
public:
    void execute(const ExecutionContext& ctx) override
    {
        ctx.m_event->reply(ctx.m_data);
    }
};


#endif //DISCORD_BOT_ADDITEMCOMMAND_H
