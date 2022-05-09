# We are using the integrated version of GoogleTest with our builds and this is only supported in CMake 3.10.0 or greater
cmake_minimum_required(VERSION 3.10.0)
project(tools VERSION 0.1.0)

# setup the minimum C++ requirements
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

# NOTE: this did not work when trying to create and link shared libraries.
# Set the default library build to shared instead of static
# option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include(FetchContent)

# To be able to use google test framework we need to fetch the source code that will be used to build
# and run this projects tests using google test framework.
FetchContent_Declare(
    googletest 
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# NOTE: For now don't build the wxWidgets library since it is not being used and is only taking cycle times for no reason.
#       Upon adding some GUI code this will be opened up once again.
#
# # To be able to use the wxWidgets GUI library we need to fetch the source code that will be used to
# # build and run this projects gui implementations.
# if(WIN32)
#     FetchContent_Declare(
#         wxWidgets
#         URL https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.5/wxWidgets-3.1.5.zip
#     )
# else()
#     FetchContent_Declare(
#         wxWidgets
#         URL https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.5/wxWidgets-3.1.5.tar.bz2
#     )
# endif()
# FetchContent_MakeAvailable(wxWidgets)

# NOTE:
# Unable to build Qt using CMake since it was not built using CMake.  So it is not worth using Qt as
# my GUI library and reverted to using wxWidgets instead since it can be built using CMake.  This does
# not imply that in the future this will not change.  It is only with respect to the current state of
# how Qt is being built at the moment.
#
# FetchContent_Declare(
#     qt
#     GIT_REPOSITORY https://github.com/qt/qtbase.git
#     GIT_TAG V6.2.4
# )
# FetchContent_MakeAvailable(qt)

# add the different sub-projects to this build
add_subdirectory(utils)
# add_subdirectory(search)
add_subdirectory(networks)
add_subdirectory(operators)
add_subdirectory(arrays)
add_subdirectory(lists)