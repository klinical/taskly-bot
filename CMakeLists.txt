cmake_minimum_required(VERSION 3.15)
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")

# Dependencies
add_subdirectory(libs/DPP)
add_subdirectory(libs/spdlog)
#add_subdirectory(libs/my_lib)

# Create executable
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/todo/todo_list.cpp
        src/todo/todo_item.cpp
        src/utils/timer.cpp
        src/utils/event.cpp
        src/types/processor.cpp
        src/types/bot_config.cpp
        src/types/application_state.cpp src/types/logger.cpp src/types/logger.h src/types/data_writer.cpp src/types/data_writer.h)

# Linking libraries
target_link_libraries(${PROJECT_NAME}
        dpp
        spdlog)

# Specify includes paths
target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
        libs/spdlog/include
        src/todo
        src/utils
        src/types)

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)