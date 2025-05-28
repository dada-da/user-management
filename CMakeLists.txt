cmake_minimum_required(VERSION 3.16)
project(payment-system)

set(CMAKE_CXX_STANDARD 20)

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
)

add_executable(${PROJECT_NAME} ${SOURCES})
