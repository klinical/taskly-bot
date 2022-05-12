cmake_minimum_required(VERSION 3.15)
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")

# Dependencies
add_subdirectory(libs/DPP)
add_subdirectory(libs/spdlog)
#add_subdirectory(libs/my_lib)

# Create executable
add_executable(${PROJECT_NAME}
        src/main.cpp
        # your others files...
#        libs/my_lib/src/my_lib.cpp libs/my_lib/include/my_lib.h
        src/todo/todo_list.cpp src/todo/todo_list.h src/todo/todo_item.cpp src/todo/todo_item.h)

# Linking libraries
target_link_libraries(${PROJECT_NAME}
        dpp
        spdlog
#        my_lib
        )

# Specify includes paths
target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
        libs/spdlog/include
#        libs/my_lib/include
        )

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )