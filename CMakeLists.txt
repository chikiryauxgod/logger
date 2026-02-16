cmake_minimum_required(VERSION 3.20)
project(c_logger C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(logger STATIC
    src/ILogger.c
    src/console_logger.c
    src/file_logger.c
    src/factory.c
)

target_include_directories(logger
    PUBLIC include
)

add_executable(logger_app
    app/main.c
)

target_link_libraries(logger_app    
    PRIVATE logger
)
