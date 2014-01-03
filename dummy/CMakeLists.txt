cmake_minimum_required (VERSION 2.6)
set(CMAKE_C_FLAGS "-g -Wall -Wextra")
project (blue-switch)

add_executable(
	dummy 
	main.c)

target_link_libraries(dummy bluetooth)

add_executable(
	rfcomm-server 
	rfcomm-server.c)

target_link_libraries(rfcomm-server bluetooth)
