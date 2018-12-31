set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -lrt")
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/alok/Desktop/misc/learn/bin/")
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
set(BOOST_ROOT "/home/alok/Desktop/misc/boost_1_68_0")
find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_directories(/home/alok/Desktop/misc/boost_1_68_0/prefix/lib)
endif()

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

link_directories(/lib/x86_64-linux-gnu)

set (Boost_USE_STATIC_LIBS ON)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -lrt")



cmake_minimum_required(VERSION 3.5)
project(learn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES_SERVER main.cpp src/UDPClient/UDPClient.cpp src/UDPClient/UDPClient.h src/UDPServer/UDPServer.cpp src/UDPServer/UDPServer.h)
set(SOURCE_FILES_CLIENT client.cpp src/UDPClient/UDPClient.cpp src/UDPClient/UDPClient.h src/UDPServer/UDPServer.cpp src/UDPServer/UDPServer.h include/udp_multicast_reciever/UDPMulticastReciever.h include/schema/Order_Message.h include/schema/Stream_Header.h include/schema/Trade_Message.h include/schema/Contract_Data.h include/schema/Depth.h include/ds/Order_Map.h include/ds/Market_Depth.h include/schema/Min_Heap_Comparator.h include/schema/Max_Heap_Comparator.h include/ds/Market_Depth_Map.h include/drivers/Redis.h include/ds/Bounded_Queue.h)
set(SOURCE_FILES_RECIEVER src/UDPMulticastReciever/UDPMulticastReciever.cpp)
set(SOURCE_FILES_SHARED_MEMORY_WRITER shared_memory_writer.cpp include/schema/Order_Message.h)
set(SOURCE_FILES_SHARED_MEMORY_READER shared_memory_reader.cpp include/schema/Order_Message.h)

add_executable(server ${SOURCE_FILES_SERVER})
add_executable(client ${SOURCE_FILES_CLIENT})
add_executable(reciever ${SOURCE_FILES_RECIEVER})
add_executable(shared_memory_reader ${SOURCE_FILES_SHARED_MEMORY_READER})
add_executable(shared_memory_writer ${SOURCE_FILES_SHARED_MEMORY_WRITER})

add_subdirectory(tests EXCLUDE_FROM_ALL)
add_subdirectory(src/UDPMulticastReciever EXCLUDE_FROM_ALL)

target_link_libraries(shared_memory_writer /lib/x86_64-linux-gnu/librt-2.23.so)