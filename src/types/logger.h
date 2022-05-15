//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_LOGGER_H
#define DISCORD_BOT_LOGGER_H


#include <memory>
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "dpp/misc-enum.h"

class logger {
public:
    typedef std::shared_ptr<spdlog::logger> logger_type;

    logger_type m_spdlog;

    void write_to_log(dpp::loglevel severity, const char* data);

    static logger_type get_instance();
private:
    // Prevent default constructor (but implement privately), initialize with a basic logger
    logger(): m_spdlog {spdlog::basic_logger_mt("logger", "log/bot.log")} { }

public:
    // Prevent all other forms of initialization, (re)assignment
    void operator= (logger const&)  = delete;
};


#endif //DISCORD_BOT_LOGGER_H
