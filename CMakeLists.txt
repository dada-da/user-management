cmake_minimum_required(VERSION 3.16)
project(payment-system)

set(CMAKE_CXX_STANDARD 20)

# Set binary output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create config directory in build folder
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/config)

# Copy config files
configure_file(${CMAKE_SOURCE_DIR}/config/database.conf
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config/database.conf
        COPYONLY)

find_path(MYSQL_INCLUDE_DIR
        NAMES mysqlx/xdevapi.h
        PATHS /usr/include /usr/local/include
        PATH_SUFFIXES mysql mysql-cppconn-8
        REQUIRED)

# Find the Connector C++ 9.2 libraries
find_library(MYSQLCPPCONN8_LIBRARY
        NAMES mysqlcppconn8
        PATHS /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
        REQUIRED)

find_library(MYSQLCPPCONN_LIBRARY
        NAMES mysqlcppconn
        PATHS /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
        REQUIRED)

find_library(MYSQLCPPCONNX_LIBRARY
        NAMES mysqlcppconnx
        PATHS /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64)

message(STATUS "MySQL Include Dir: ${MYSQL_INCLUDE_DIR}")
message(STATUS "MySQL Connector/C++ 8 Library: ${MYSQLCPPCONN8_LIBRARY}")
message(STATUS "MySQL Connector/C++ Library: ${MYSQLCPPCONN_LIBRARY}")
if(MYSQLCPPCONNX_LIBRARY)
    message(STATUS "MySQL X DevAPI Library: ${MYSQLCPPCONNX_LIBRARY}")
endif()

# Include directories
include_directories(
        ${MYSQL_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

# Source files
set(SOURCES
        src/main.cpp
        src/database/db_connection.cpp
        src/database/db_connection.h
        src/database_config/database_config.cpp
        src/database_config/database_config.h
        src/database_constants/user_table.h
        src/database_constants/user_queries.h
        src/database_constants/wallet_table.h
        src/database_constants/wallet_queries.h
        src/database_constants/transaction_table.h
        src/database_constants/transaction_queries.h
        src/menu_system/menu_system.cpp
        src/menu_system/menu_system.h
        src/user/user.h
        src/user/user_management.cpp
        src/user/user_management.h
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link with the MySQL libraries
if(MYSQLCPPCONNX_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${MYSQLCPPCONNX_LIBRARY} ${MYSQLCPPCONN8_LIBRARY} ${MYSQLCPPCONN_LIBRARY})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${MYSQLCPPCONN8_LIBRARY} ${MYSQLCPPCONN_LIBRARY})
endif()

# Enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Add debug/release specific flags
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE)
endif ()

# Installation rules
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
)

install(FILES ${CMAKE_SOURCE_DIR}/config/database.conf
        DESTINATION config
)

# Print configuration summary
message(STATUS "----------------------------------------")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "----------------------------------------")