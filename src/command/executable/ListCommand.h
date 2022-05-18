//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_LISTCOMMAND_H
#define DISCORD_BOT_LISTCOMMAND_H

#include "registry/CommandRegistrarEntry.h"
#include "ICommandExecutable.h"

class ListCommand: public ICommandExecutable {
public:
    void execute(const ExecutionContext& ctx) const override
    {
        // todo, actually use data
        ctx.m_event->reply("Something works lmao");
    }
};


#endif //DISCORD_BOT_LISTCOMMAND_H
