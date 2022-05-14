//
// Created by zach on 5/11/22.
//

#include "todo_list.h"

void todo_list::add_item(todo_item item) {
    m_items.push_back(item);
}

std::vector<todo_item> todo_list::get_items() {
    return m_items;
}

std::string todo_list::str() {
    std::string str {};

    // Build up response string
    for (todo_item& item : m_items) {
        str += "owner: " + item.owner + " message: " + item.message + '\n';
    }

    return str;
}