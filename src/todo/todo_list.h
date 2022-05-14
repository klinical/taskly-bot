//
// Created by zach on 5/11/22.
//

#ifndef DISCORD_BOT_TODO_LIST_H
#define DISCORD_BOT_TODO_LIST_H

#include <vector>
#include "todo_item.h"

class todo_list {
    std::vector<todo_item> m_items;

public:
    // Default constructor
    todo_list() = default;

    void add_item(todo_item item);
    std::vector<todo_item> get_items();
    std::string str();
};


#endif //DISCORD_BOT_TODO_LIST_H
