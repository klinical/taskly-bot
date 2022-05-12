//
// Created by zach on 5/11/22.
//

#include "todo_list.h"

void todo_list::add_item(todo_item item) {
    items.push_back(item);
}

std::vector<todo_item> todo_list::get_items() {
    return items;
}