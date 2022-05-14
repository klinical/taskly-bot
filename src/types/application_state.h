//
// Created by zach on 5/13/22.
//

#ifndef DISCORD_BOT_APPLICATION_STATE_H
#define DISCORD_BOT_APPLICATION_STATE_H

#include "processor.h"
#include "todo_list.h"
#include "timer.h"
#include "spdlog/logger.h"

class application_state {
public:
    typedef std::shared_ptr<spdlog::logger> spdlog_ref;

private:
    bot_config m_config { bot_config::from_flat_file("../bot.cfg") };
    todo_list m_todo_list { };
    processor processor { m_config, m_todo_list };

};

#endif //DISCORD_BOT_APPLICATION_STATE_H
