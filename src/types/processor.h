//
// Created by zach on 5/13/22.
//

#ifndef DISCORD_BOT_PROCESSOR_H
#define DISCORD_BOT_PROCESSOR_H

#include <dpp/dpp.h>

#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "dpp/cluster.h"
#include "bot_config.h"
#include "todo_list.h"
#include "logger.h"
#include "data_writer.h"

class processor {
private:
    dpp::cluster m_cluster;
    todo_list m_list;
    data_writer m_data_writer;

    static void create_command(dpp::cluster& bot, const dpp::slashcommand&, dpp::snowflake guild_id);

public:
    processor(const bot_config& config, todo_list& list);
};


#endif //DISCORD_BOT_PROCESSOR_H
