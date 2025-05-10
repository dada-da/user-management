cmake_minimum_required(VERSION 3.16)
project(payment-system)

set(CMAKE_CXX_STANDARD 20)

# Find Homebrew MySQL connector paths
execute_process(
        COMMAND brew --prefix mysql-connector-c++
        OUTPUT_VARIABLE MYSQL_CONNECTOR_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "MySQL Connector Directory: ${MYSQL_CONNECTOR_DIR}")


# Copy config files
configure_file(${CMAKE_SOURCE_DIR}/config/database.conf
        ${CMAKE_BINARY_DIR}/config/database.conf
        COPYONLY)


# Include directories
include_directories(
        ${MYSQL_CONNECTOR_DIR}/include
)

# Add executable
add_executable(payment-system src/main.cpp
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
        src/user/user_management.h)

# Find the X DevAPI library
find_library(MYSQLCPPCONNX_LIBRARY
        NAMES mysqlcppconnx libmysqlcppconnx
        PATHS "${MYSQL_CONNECTOR_DIR}/lib"
)

message(STATUS "MySQL X DevAPI Library: ${MYSQLCPPCONNX_LIBRARY}")

# If library not found with find_library, use direct path
if (NOT MYSQLCPPCONNX_LIBRARY)
    set(MYSQLCPPCONNX_LIBRARY "${MYSQL_CONNECTOR_DIR}/lib/libmysqlcppconnx.dylib")
    message(STATUS "Using direct path to library: ${MYSQLCPPCONNX_LIBRARY}")
endif ()

# Link with the library
target_link_libraries(payment-system ${MYSQLCPPCONNX_LIBRARY})

# Set RPATH
set_target_properties(payment-system PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "${MYSQL_CONNECTOR_DIR}/lib"
)