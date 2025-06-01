cmake_minimum_required(VERSION 3.16)
project(payment-system)

set(CMAKE_CXX_STANDARD 20)

add_custom_target(copy_database_files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/database
        ${CMAKE_BINARY_DIR}/database
        COMMENT "Copying database files"
)

set(SOURCES
        src/main.cpp
        src/user/customer.h
        src/user/admin.h
        src/user_management/user_management.cpp
        src/user_management/user_management.h
        src/role/role.cpp
        src/role/role.h
        src/menu_controller/menu_controller.cpp
        src/menu_controller/menu_controller.h
        src/user_data/user_data.cpp
        src/user_data/user_data.h
        src/file_controller/file_controller.h
        src/password_manager/password_manager.cpp
        src/password_manager/password_manager.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME}  copy_database_files)