//
// Created by zach on 5/13/22.
//

#ifndef DISCORD_BOT_EVENT_H
#define DISCORD_BOT_EVENT_H

#include "dpp/dispatcher.h"

class log_event: public dpp::log_t {

public:
    // Member fn


    // Overloads
    friend std::ostream& operator<< (std::ostream& out, const log_event& event);

    // Constructors
    explicit log_event(const dpp::log_t& event) : dpp::log_t { event } { }
};


#endif //DISCORD_BOT_EVENT_H
