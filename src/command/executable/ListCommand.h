//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_LISTCOMMAND_H
#define DISCORD_BOT_LISTCOMMAND_H

#include "ICommandExecutable.h"

class ListCommand: public ICommandExecutable {
public:
    void execute(const ExecutionContext& ctx) const override
    {
        auto cmd_data = ctx.m_event->command.get_command_interaction();

        if (!cmd_data.options.empty())
        {
            std::string str{ std::get<std::string>(cmd_data.options[0].options[0].value) };
            std::cout << str << std::endl;
//            ctx.m_event->reply(cmd_data.options[0].name);
            ctx.m_event->reply(str);
        }
        else
        {
            DataManager::ListMap* writer_data = ctx.m_writer->full_list();

            std::stringstream ss;

            for (const auto& [list_key, list_items] : *writer_data)
            {
                ss << "[" << list_key << "]\n";

                int i{ };
                for (const auto& list_item : *list_items)
                {
                    ++i;
                    ss << i << ". " << list_item << '\n';
                }
            }

            ctx.m_event->reply(ss.str());
        }
    }
};


#endif //DISCORD_BOT_LISTCOMMAND_H
