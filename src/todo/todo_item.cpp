//
// Created by zach on 5/11/22.
//

#include "todo_item.h"

#include <string>
#include <sstream>
#include <utility>

/**
 * Create a formatted/pretty printed string representation of a todo_item for debug or logging purposes
 * @return str a debug string representation of a to_do item
 */
std::string todo_item::str() const {
    std::stringstream ss;
    ss << "todo_item { "
       << owner
       << " , "
       << message
       << " }";

    return ss.str();
}

// Overloads

// IO
std::ostream& operator<< (std::ostream& out, const todo_item& item) {
    out << "(" << item.owner << 31 << item.message << ")";

    // Returning the ostream so that caller can continue chaining e.g.
    // cout << item << " another string";
    return out;
}

// Equality
bool operator== (const todo_item& item_a, const todo_item& item_b) {
    return (item_a.owner == item_b.owner && item_a.message == item_b.message);
}

bool operator!= (const todo_item& item_a, const todo_item& item_b) {
    return !(item_a.owner == item_b.owner && item_a.message == item_b.message);
}

// String formatting
std::string operator+(const char *str, const todo_item &item) {
    return str + item.str();
}

std::string operator+(const todo_item &item, const char *str) {
    return item.str() + str;
}

// Constructor
// Take in string params and move ownership to member vars
todo_item::todo_item(std::string   owner_, std::string   message_)
        : owner { std::move(owner_) }, message { std::move(message_) } { }