# @author  Barthélémy von Haller

set(BOOST_ROOT "/home/alok/Desktop/misc/boost_1_68_0/prefix/")
find_package(Boost)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

FIND_PACKAGE(Boost 1.68.0 COMPONENTS log REQUIRED)
set (Boost_USE_STATIC_LIBS ON)

set(SOURCE_FILES_SERVER UDPMulticastReciever.cpp)

set(INCLUDE_DIRECTORY "/home/alok/Desktop/misc/learn/include/ /home/alok/Desktop/misc/boost_1_68_0/")
set(LINK_DIRECTORY /home/alok/Desktop/misc/boost_1_68_0/prefix/lib/ /home/alok/Desktop/misc/learn/third_party/)

link_directories(${LINK_DIRECTORY})
add_executable(UDPMultiCastReciever ${SOURCE_FILES_SERVER} )

target_include_directories(UDPMultiCastReciever PRIVATE ${INCLUDE_DIRECTORY} )
target_link_libraries(UDPMultiCastReciever boost_thread boost_timer boost_system boost_chrono lzo pthread)

#foreach(FILE ${TEST_FILES})
#    string(REGEX REPLACE "[./]" "_" NAME ${FILE}) # create exe name
#    add_executable(${NAME} ${FILE})
##    target_link_libraries(${NAME} ProjB ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}) # link against our lib and boost test
##    add_test(NAME ${NAME} COMMAND ${NAME})                              # this is how to add tests to CMake
#endforeach(FILE ${TEST_FILES})


#include(CTest)