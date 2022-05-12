//
// Created by zach on 5/11/22.
//

#include "todo_item.h"

#include <string>
#include <sstream>

std::string todo_item::serialize() {
    std::stringstream ss;
    ss << owner
        << ":"
        << message
        << ";";

    return ss.str();
}

// Constructor
// Take in string params and move ownership to member vars
todo_item::todo_item(const std::string&  owner_, const std::string&  message_)
        : owner {std::move( owner_ )}, message {std::move( message_ )} { }