//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_EXECUTIONCONTEXTBUILDER_H
#define DISCORD_BOT_EXECUTIONCONTEXTBUILDER_H

#include <utility>

#include "dpp/dispatcher.h"
#include "dpp/cluster.h"
#include "ExecutionContext.h"
#include "spdlog/logger.h"

class ExecutionContextBuilder {
private:
    const dpp::interaction_create_t* m_event;
    const dpp::cluster* m_cluster;
    std::shared_ptr<spdlog::logger> m_logger;
    std::string m_writer;

public:
    [[nodiscard]]
    ExecutionContextBuilder& set_event(const dpp::interaction_create_t& event) {
        m_event = &event;

        return *this;
    }

    ExecutionContextBuilder& set_cluster(const dpp::cluster& cluster) {
        m_cluster = &cluster;

        return *this;
    }

    ExecutionContextBuilder& set_logger(std::shared_ptr<spdlog::logger> logger) {
        m_logger = std::move(logger);

        return *this;
    }

    ExecutionContextBuilder& set_writer(std::string writer) {
        m_writer = std::move(writer);

        return *this;
    }

    /**
     * Todo, error handling
     * @return
     */
    ExecutionContext build()
    {
        return ExecutionContext{ m_event, m_cluster, m_logger };
    }
};


#endif //DISCORD_BOT_EXECUTIONCONTEXTBUILDER_H
