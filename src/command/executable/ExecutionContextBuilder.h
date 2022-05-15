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
    ExecutionContext ctx{ };

public:
    [[nodiscard]]
    ExecutionContextBuilder& event(const dpp::interaction_create_t& event) {
        ctx.m_event = &event;

        return *this;
    }

    ExecutionContextBuilder& cluster(const dpp::cluster& cluster) {
        ctx.m_cluster = &cluster;

        return *this;
    }

    ExecutionContextBuilder& logger(std::shared_ptr<spdlog::logger> logger) {
        ctx.m_logger = std::move(logger);

        return *this;
    }

    ExecutionContextBuilder& data(std::string data) {
        ctx.m_data = std::move(data);

        return *this;
    }

    /**
     * Todo, error handling
     * @return
     */
    ExecutionContext& build()
    {
        return ctx;
    }
};


#endif //DISCORD_BOT_EXECUTIONCONTEXTBUILDER_H
