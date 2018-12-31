# @author  Barthélémy von Haller

set(SOURCE_FILES_SERVER Bounded_Queue_Test.cpp ../include/ds/Bounded_Queue.h)
set(SOURCE_FILES_SERIALIZER Map_Serializer.cpp)

set(INCLUDE_DIRECTORY "/home/alok/Desktop/misc/learn/include/ /home/alok/Desktop/misc/boost_1_68_0/")
set(LINK_DIRECTORY /home/alok/Desktop/misc/boost_1_68_0/prefix/lib/)

link_directories(${LINK_DIRECTORY})
add_executable(Bounded_Queue_Test ${SOURCE_FILES_SERVER} )

target_include_directories(Bounded_Queue_Test PRIVATE ${INCLUDE_DIRECTORY} )
target_link_libraries(Bounded_Queue_Test boost_thread boost_timer boost_system boost_chrono pthread)

add_executable(Map_Serializer ${SOURCE_FILES_SERIALIZER} )

target_include_directories(Map_Serializer PRIVATE ${INCLUDE_DIRECTORY} )
target_link_libraries(Map_Serializer boost_serialization)

#foreach(FILE ${TEST_FILES})
#    string(REGEX REPLACE "[./]" "_" NAME ${FILE}) # create exe name
#    add_executable(${NAME} ${FILE})
##    target_link_libraries(${NAME} ProjB ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}) # link against our lib and boost test
##    add_test(NAME ${NAME} COMMAND ${NAME})                              # this is how to add tests to CMake
#endforeach(FILE ${TEST_FILES})


#include(CTest)