//
// Created by zach on 5/14/22.
//

#ifndef DISCORD_BOT_DATA_WRITER_H
#define DISCORD_BOT_DATA_WRITER_H

#include "todo_item.h"

class data_writer {
public:
    static void write_new_todo_item(const todo_item& item);

    data_writer();
};


#endif //DISCORD_BOT_DATA_WRITER_H
