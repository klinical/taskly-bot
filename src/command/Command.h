//
// Created by zach on 5/17/22.
//

#ifndef DISCORD_BOT_COMMAND_H
#define DISCORD_BOT_COMMAND_H


#include <vector>
#include <string>
#include "dpp/appcommand.h"
#include "executable/ICommandExecutable.h"

class Command {
public:
    dpp::slashcommand* m_cmd;
    ICommandExecutable* m_executor;

    Command(dpp::slashcommand* cmd, ICommandExecutable* executor)
        : m_cmd{ cmd }, m_executor{ executor }
    { };
};


#endif //DISCORD_BOT_COMMAND_H
