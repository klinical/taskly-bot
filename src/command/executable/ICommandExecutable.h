//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_ICOMMANDEXECUTABLE_H
#define DISCORD_BOT_ICOMMANDEXECUTABLE_H


#include <utility>

#include "ExecutionContext.h"

class ICommandExecutable {
public:
    // Pure virtual function
    virtual void execute(const ExecutionContext& ctx) const = 0;
};


#endif //DISCORD_BOT_ICOMMANDEXECUTABLE_H
