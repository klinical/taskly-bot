#include "todo/todo_list.h"

#include <dpp/dpp.h>
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "types/application_state.h"

#include <string>

int main() {
    // Logger init
    // todo, allow multiple loggers, log level, etc
    spdlog::flush_every(std::chrono::seconds(5));

    // Init state
    application_state app_state {  };

    return 0;
}