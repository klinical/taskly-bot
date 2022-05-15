//
// Created by zach on 5/14/22.
//

#include "logger.h"

void logger::write_to_log(dpp::loglevel severity, const char* data) {
    switch (severity) {
        // Must dereference m_spdlg
        case dpp::ll_critical:
            m_spdlog->critical(data);
            break;
        case dpp::ll_error:
            m_spdlog->error("{}", data);
            break;
        default:
            m_spdlog->info("{}", data);
            break;
    }
}

logger::logger_type logger::get_instance() {
    static logger_type instance { spdlog::basic_logger_mt("logger", "log/bot.log") };

    return instance;
}