//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_EXECUTIONCONTEXT_H
#define DISCORD_BOT_EXECUTIONCONTEXT_H


#include <utility>

#include "dpp/cluster.h"
#include "spdlog/logger.h"
#include "DataManager.h"

/**
 * Fluent design, ExecutionContext must be constructed by a builder which sets all of it's fields
 * using named methods.
 */
class ExecutionContext {
public:
    const dpp::interaction_create_t* m_event{};

    DataManager* m_writer;
    std::shared_ptr<spdlog::logger> m_logger;

private:
    ExecutionContext() = default;

    [[maybe_unused]]
    ExecutionContext(
            const dpp::interaction_create_t *pCreate,
            std::shared_ptr<spdlog::logger> pLogger,
            DataManager* writer
    ):
            m_event{ pCreate },
            m_logger{std::move( pLogger )},
            m_writer{ writer }
    { };

    friend class ExecutionContextBuilder;
};


#endif //DISCORD_BOT_EXECUTIONCONTEXT_H
