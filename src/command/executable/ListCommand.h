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
        DataManager::ListMap* writer_data = ctx.m_writer->full_list();

        std::stringstream ss;

        for (const auto& [list_key, list_items] : *writer_data)
        {
            ss << "[" << &list_key << "]\n";

            int i{ };
            for (const auto& list_item : list_items)
            {
                ++i;
                ss << i << ". " << &list_item << '\n';
            }
        }

        ctx.m_event->reply(ss.str());
    }
};


#endif //DISCORD_BOT_LISTCOMMAND_H
