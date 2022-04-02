cmake_minimum_required(VERSION 3.0.0)
project(ipc-utils VERSION 0.1.0)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED true)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
#set_target_properties(ipc-utils-test PROPERTIES _OS_TYPE_ ${CMAKE_SYSTEM_NAME})

# option(FOO_ENABLE "Enable Foo" ON)
# if(FOO_ENABLE)
#   set(FOO_STRING "foo")
# endif()
# option(_OS_TYPE_ENABLE_ "Enable Os_Type" ON)
# if(_OS_TYPE_ENABLE_)
#   set(_OS_TYPE_ "Windows")
# endif()

# if(CMAKE_SYSTEM_NAME EQUAL "Windows")
#     set(OS_TYPE_NAME "Windows")
# elseif(${CMAKE_SYSTEM_NAME} EQUAL "Linux")
#     set(OS_TYPE_NAME "Linux")
# elseif(${CMAKE_SYSTEM_NAME} EQUAL "Darwin")
#     set(OS_TYPE_NAME "MacOS")
# else()
#     set(OS_TYPE_NAME "Unknown")
# endif()

configure_file(config.h.in config.h @ONLY)
# set(_OS_TYPE_NAME_ ${CMAKE_SYSTEM_NAME})
# configure_file(config.h.in config.h @ONLY)

add_library(ipc-utils ipc-utils.cpp shared_memory.cpp)
add_executable(ipc-utils-command tests.cpp)
add_test(NAME ipc-utils-test COMMAND ipc-utils-command ${CMAKE_SYSTEM_NAME} ${OS_TYPE_NAME})

# set_tests_properties(ipc-utils-test PROPERTIES _OS_TYPE_ ${CMAKE_SYSTEM_NAME})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
