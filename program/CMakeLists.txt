cmake_minimum_required(VERSION 3.4)

project(Biblioteka)

#specify set of project's source files
set(SOURCE_FILES
        src/main.cpp
        )
#add following files to executable file 'Biblioteka'
add_executable(Biblioteka ${SOURCE_FILES})

#add libraries from 'Library' project
target_link_libraries(Biblioteka Library)

#add header files from 'include' directory of main project
target_include_directories(Biblioteka PUBLIC include)
