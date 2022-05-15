//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_COMMANDEXECUTABLE_H
#define DISCORD_BOT_COMMANDEXECUTABLE_H


#include <utility>

#include "ExecutionContext.h"

class CommandExecutable {
public:
    std::vector<dpp::command_option> options {};

    CommandExecutable() = default;
    virtual void execute(const ExecutionContext& ctx)
    {};
};


#endif //DISCORD_BOT_COMMANDEXECUTABLE_H
