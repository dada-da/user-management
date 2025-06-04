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
        src/user_management/user_management.cpp
        src/user_management/user_management.h
        src/role/role.cpp
        src/role/role.h
        src/menu_controller/menu_controller.cpp
        src/menu_controller/menu_controller.h
        src/user_data/user_data.h
        src/user_data/user_data.cpp
        src/utils/list/list.h
        src/service/authentication/authentication_service.cpp
        src/service/authentication/authentication_service.h
        src/utils/password_handler/password_handler.cpp
        src/utils/password_handler/password_handler.h
        src/user_data/interface_user_data.h
        src/service/authentication/interface_authentication_service.h
        src/menu_controller/menu_list.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} copy_database_files)