//
// Created by zach on 5/13/22.
//


#include "event.h"
#include <iostream>

std::string loglevel_to_str(dpp::loglevel ll);

std::ostream& operator<< (std::ostream& out, const log_event& event) {
    const std::string message = event.message;
    const std::string ll = loglevel_to_str(event.severity);

    out << "(" << ll << ", " << message << ")";
    return out;
}

std::string loglevel_to_str(dpp::loglevel ll) {
    std::string ll_str;

    switch (ll) {
        case dpp::ll_info:
            ll_str = "OK";
            break;
        case dpp::ll_error:
        case dpp::ll_warning:
        case dpp::ll_critical:
        case dpp::ll_trace:
        case dpp::ll_debug:
            ll_str = "ERR";
            break;
    }

    return ll_str;
}
