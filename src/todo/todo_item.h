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

    // [[nodiscard]] - Flag for function's who's return values, when ignored, are likely done so accidentally
    // e.g., is there any reason a caller wouldn't use the string produced by this function? (Why would they call it?)
    [[nodiscard]] std::string str() const;
    todo_item(std::string   owner_, std::string   message_);

    // Overloads
    friend std::ostream& operator<< (std::ostream& out, const todo_item& item);
    friend bool operator== (const todo_item& item_a, const todo_item& item_b);
    friend bool operator!= (const todo_item& item_a, const todo_item& item_b);
    friend std::string operator+ (const todo_item& item, const char* str);
    friend std::string operator+ (const char* str, const todo_item& item);
};


#endif //DISCORD_BOT_TODO_ITEM_H
