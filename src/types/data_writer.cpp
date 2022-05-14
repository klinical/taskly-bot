//
// Created by zach on 5/14/22.
//

#include <fstream>
#include "data_writer.h"
#include "logger.h"

void data_writer::write_new_todo_item(const todo_item& item) {
    // Open file for writing in app(end) mode
    std::ofstream todo_file;
    todo_file.open("todo_data", std::ofstream::app);

    todo_file << item;
    todo_file.close();

    logger::get_instance()->info("Wrote new todo item: " + item);
}