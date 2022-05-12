//
// Created by zach on 5/11/22.
//

#ifndef DISCORD_BOT_TODO_ITEM_H
#define DISCORD_BOT_TODO_ITEM_H

#include <string>

class todo_item {
public:
    std::string owner;
    std::string message;

    std::string serialize();
    todo_item(const std::string&  owner_, const std::string&  message_);
};


#endif //DISCORD_BOT_TODO_ITEM_H
