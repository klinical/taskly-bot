//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_ADDITEMCOMMAND_H
#define DISCORD_BOT_ADDITEMCOMMAND_H

#include "ExecutionContext.h"
#include "ICommandExecutable.h"

class AddItemCommand: public ICommandExecutable {
public:
    void execute(const ExecutionContext& ctx) const override
    {
        ctx.m_event->reply("erm");
    }
};


#endif //DISCORD_BOT_ADDITEMCOMMAND_H
