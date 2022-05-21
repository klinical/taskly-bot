cmake_minimum_required(VERSION 3.15)
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")

# Dependencies
add_subdirectory(libs/DPP)
add_subdirectory(libs/spdlog)
#add_subdirectory(libs/my_lib)

# Create executable
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/types/logger.cpp
        src/bot/DiscordBot.cpp
        src/bot/BotConfig.cpp
        src/data/DataManager.cpp
        src/command/registry/CommandRegistrar.cpp
        src/command/executable/ExecutionContextBuilder.cpp
        src/command/executable/ExecutionContext.cpp
        src/command/executable/ListCommand.cpp
        src/command/executable/AddItemCommand.cpp
        src/command/SlashCommandFactory.cpp
        src/command/Command.cpp
        src/types/SimplePtr.cpp src/utils/util.cpp src/utils/util.h)

# Linking libraries
target_link_libraries(${PROJECT_NAME}
        dpp
        spdlog)

# Specify includes paths
target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
        libs/spdlog/include
        libs/json
        src/bot
        src/command
        src/data
        src/types
        src/utils)

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)