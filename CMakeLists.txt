cmake_minimum_required(VERSION 3.16)
project(dining_philosophers)

set( CMAKE_INCLUDE_PATH "/usr/include")
set( CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/libncurses.so")
set(CMAKE_CXX_STANDARD 17)

add_executable(dining_philosophers main.cpp objects/Philosopher.cpp objects/Philosopher.h objects/Chopstick.cpp objects/Chopstick.h objects/Waiter.cpp objects/Waiter.h)

# Look for the package you want to link
find_package( Curses REQUIRED )
find_package( Threads )

# Include the directories of the package (to find curses.h for instance)
target_include_directories(${PROJECT_NAME} PRIVATE ${CURSES_INCLUDE_DIRS} )

# Link the library
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES} )
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT} )