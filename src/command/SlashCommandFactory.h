//
// Created by zach on 5/17/22.
//

#ifndef DISCORD_BOT_SLASHCOMMANDFACTORY_H
#define DISCORD_BOT_SLASHCOMMANDFACTORY_H


#include <string>
#include <utility>
#include <vector>
#include "dpp/appcommand.h"
#include "Command.h"
#include "dpp/cluster.h"
#include "executable/ICommandExecutable.h"

class SlashCommandFactory {
private:
    std::string m_title;
    std::string m_desc;

    dpp::snowflake m_app_id;

    ICommandExecutable* m_executor{ };
    std::vector<dpp::command_option> m_options;

public:
    explicit SlashCommandFactory() = default;
    SlashCommandFactory& title(std::string title)
    {
        m_title = std::move(title);

        return *this;
    }

    SlashCommandFactory& desc(std::string desc)
    {
        m_desc = std::move(desc);

        return *this;
    }

    SlashCommandFactory& app_id(dpp::snowflake app_id)
    {
        m_app_id = app_id;

        return *this;
    }

    SlashCommandFactory& options(const std::vector<dpp::command_option>& options)
    {
        m_options = options;

        return *this;
    }

    SlashCommandFactory& executor(ICommandExecutable* executor)
    {
        m_executor = executor;
    }

    [[nodiscard]]
    Command build()
    {
        auto* cmd = new dpp::slashcommand { m_title, m_desc, m_app_id };

        if (!m_options.empty())
            for (const dpp::command_option &option: m_options) {
                cmd->add_option(option);
            }

        auto temp = m_executor;

        // Reset the builder for re-use
        this->reset();
        return Command { cmd, temp };
    }

    void reset()
    {
        m_title = "";
        m_executor = nullptr;
        m_desc = "";
        m_options.clear();
    }
};


#endif //DISCORD_BOT_SLASHCOMMANDFACTORY_H
