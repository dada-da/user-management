cmake_minimum_required(VERSION 3.16)
project(user-management)

set(CMAKE_CXX_STANDARD 20)

# Copy config files
configure_file(${CMAKE_SOURCE_DIR}/config/database.conf
        ${CMAKE_BINARY_DIR}/config/database.conf
        COPYONLY)

# Find Homebrew MySQL connector paths
execute_process(
        COMMAND brew --prefix mysql-connector-c++
        OUTPUT_VARIABLE MYSQL_CONNECTOR_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "MySQL Connector Directory: ${MYSQL_CONNECTOR_DIR}")

# Include directories
include_directories(
        ${MYSQL_CONNECTOR_DIR}/include
)

# Add executable
add_executable(user-management src/main.cpp
        src/config_loader/ConfigLoader.cpp
        src/config_loader/ConfigLoader.h
        src/database/MySQLConnection.cpp
        src/database/MySQLConnection.h)

# Find the X DevAPI library
find_library(MYSQLCPPCONNX_LIBRARY
        NAMES mysqlcppconnx libmysqlcppconnx
        PATHS "${MYSQL_CONNECTOR_DIR}/lib"
)

message(STATUS "MySQL X DevAPI Library: ${MYSQLCPPCONNX_LIBRARY}")

# If library not found with find_library, use direct path
if(NOT MYSQLCPPCONNX_LIBRARY)
    set(MYSQLCPPCONNX_LIBRARY "${MYSQL_CONNECTOR_DIR}/lib/libmysqlcppconnx.dylib")
    message(STATUS "Using direct path to library: ${MYSQLCPPCONNX_LIBRARY}")
endif()

# Link with the library
target_link_libraries(user-management ${MYSQLCPPCONNX_LIBRARY})

# Set RPATH
set_target_properties(user-management PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "${MYSQL_CONNECTOR_DIR}/lib"
)