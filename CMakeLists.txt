cmake_minimum_required(VERSION 3.30)
project(imobiliaria_BD)
set(MySQL_INCLUDE_DIR "/usr/include/mysql")

include_directories(${MySQL_INCLUDE_DIR})
link_directories(${MySQL_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 20)

add_executable(imobiliaria_BD main.cpp
        database/settings.cpp
        database/settings.h
        database/tables/BaseTable.cpp
        database/tables/BaseTable.h
        database/tables/Inquilino.cpp
        database/tables/Inquilino.h
        database/tables/Fiador.cpp
        database/tables/Fiador.h)

target_link_libraries(imobiliaria_BD mysqlclient)
