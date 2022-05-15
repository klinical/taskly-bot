//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_EXECUTIONCONTEXT_H
#define DISCORD_BOT_EXECUTIONCONTEXT_H


#include <utility>

#include "dpp/cluster.h"
#include "spdlog/logger.h"

/**
 * Fluent design, ExecutionContext must be constructed by a builder which sets all of it's fields
 * using named methods.
 */
class ExecutionContext {
public:
    const dpp::interaction_create_t* m_event{};
    const dpp::cluster* m_cluster{};
    std::string m_data{};
    std::shared_ptr<spdlog::logger> m_logger;

private:
    ExecutionContext() = default;

    [[maybe_unused]]
    ExecutionContext(
            const dpp::interaction_create_t *pCreate,
            const dpp::cluster *pCluster,
            std::shared_ptr<spdlog::logger> pLogger
    ):
            m_event{ pCreate },
            m_cluster{ pCluster },
            m_logger{std::move( pLogger )}
    { };

    friend class ExecutionContextBuilder;
};


#endif //DISCORD_BOT_EXECUTIONCONTEXT_H
