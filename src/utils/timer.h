//
// Created by zach on 5/13/22.
//

#ifndef DISCORD_BOT_TIMER_H
#define DISCORD_BOT_TIMER_H

#include <chrono>

class timer {
private:
    using clock_type = std::chrono::steady_clock;
    using seconds_type = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_type> m_beginning { clock_type::now() };

public:
    void reset();
    double elapsed() const;
};


#endif //DISCORD_BOT_TIMER_H
