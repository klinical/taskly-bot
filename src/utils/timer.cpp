//
// Created by zach on 5/13/22.
//

#include "timer.h"

void timer::reset() {
    m_beginning = clock_type::now();
}

double timer::elapsed() const {
    return std::chrono::duration_cast<seconds_type>(clock_type::now() - m_beginning).count();
}