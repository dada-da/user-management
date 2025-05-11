cmake_minimum_required(VERSION 3.16)
project(payment-system)

set(CMAKE_CXX_STANDARD 20)

# Platform-specific MySQL Connector/C++ configuration
if (WIN32)
    # Windows configuration for MySQL Connector/C++ 9.2
    set(MYSQL_CONNECTOR_DIR "C:/Program Files/MySQL/MySQL Connector C++ 9.2"
            CACHE PATH "Path to MySQL Connector C++ installation")

    # Check if the path exists
    if (NOT EXISTS ${MYSQL_CONNECTOR_DIR})
        message(FATAL_ERROR "MySQL Connector/C++ not found at ${MYSQL_CONNECTOR_DIR}. "
                "Please install it or set MYSQL_CONNECTOR_DIR correctly.")
    endif ()

    # Set include directory
    set(MYSQL_INCLUDE_DIR "${MYSQL_CONNECTOR_DIR}/include")

    # Find the library
    find_library(MYSQLCPPCONNX_LIBRARY
            NAMES mysqlcppconn9 mysqlcppconn
            PATHS ${MYSQL_CONNECTOR_DIR}
            NO_DEFAULT_PATH
    )

elseif (APPLE)
    # macOS configuration with Homebrew
    execute_process(
            COMMAND brew --prefix mysql-connector-c++
            OUTPUT_VARIABLE MYSQL_CONNECTOR_DIR
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(MYSQL_INCLUDE_DIR "${MYSQL_CONNECTOR_DIR}/include")

    # Find the X DevAPI library
    find_library(MYSQLCPPCONNX_LIBRARY
            NAMES mysqlcppconnx libmysqlcppconnx
            PATHS "${MYSQL_CONNECTOR_DIR}/lib64"
    )

    # If library not found with find_library, use direct path
    if (NOT MYSQLCPPCONNX_LIBRARY)
        set(MYSQLCPPCONNX_LIBRARY "${MYSQL_CONNECTOR_DIR}/lib64/libmysqlcppconnx.dylib")
    endif ()

elseif (UNIX)
    # Linux configuration
    find_package(PkgConfig)
    if (PkgConfig_FOUND)
        pkg_check_modules(MYSQLCPPCONN mysqlcppconn)
    endif ()

    if (NOT MYSQLCPPCONN_FOUND)
        # Fallback to standard paths
        set(MYSQL_CONNECTOR_DIR "/usr" CACHE PATH "Path to MySQL Connector C++ installation")
        set(MYSQL_INCLUDE_DIR "${MYSQL_CONNECTOR_DIR}/include")
        find_library(MYSQLCPPCONNX_LIBRARY
                NAMES mysqlcppconnx mysqlcppconn mysqlcppconn9
                PATHS "${MYSQL_CONNECTOR_DIR}/lib" "${MYSQL_CONNECTOR_DIR}/lib64"
        )
    endif ()
endif ()

message(STATUS "MySQL Connector Directory: ${MYSQL_CONNECTOR_DIR}")
message(STATUS "MySQL Include Directory: ${MYSQL_INCLUDE_DIR}")
message(STATUS "MySQL Library: ${MYSQLCPPCONNX_LIBRARY}")

# Copy config files
configure_file(${CMAKE_SOURCE_DIR}/config/database.conf
        ${CMAKE_BINARY_DIR}/config/database.conf
        COPYONLY)

# Create config directory in build folder
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/config)

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

# Link with the library
target_link_libraries(${PROJECT_NAME} PRIVATE ${MYSQLCPPCONNX_LIBRARY})

# Platform-specific settings
if (WIN32)
    # Set Visual Studio specific properties
    set_target_properties(${PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )

    # Copy required DLLs to output directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MYSQL_CONNECTOR_DIR}/lib64/mysqlcppconnx-2-vs14.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    # Copy SSL libraries if they exist
    if (EXISTS "${MYSQL_CONNECTOR_DIR}/lib64/libssl-3-x64.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MYSQL_CONNECTOR_DIR}/lib64/libssl-3-x64.dll"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif ()

    if (EXISTS "${MYSQL_CONNECTOR_DIR}/lib64/libcrypto-3-x64.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MYSQL_CONNECTOR_DIR}/lib64/libcrypto-3-x64.dll"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif ()

elseif (APPLE)
    # Set RPATH for macOS
    set_target_properties(${PROJECT_NAME} PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            INSTALL_RPATH "${MYSQL_CONNECTOR_DIR}/lib"
    )
elseif (UNIX)
    # Set RPATH for Linux
    set_target_properties(${PROJECT_NAME} PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            INSTALL_RPATH "${MYSQL_CONNECTOR_DIR}/lib"
    )
endif ()

# Enable warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX-)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif ()

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