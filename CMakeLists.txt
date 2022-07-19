cmake_minimum_required(VERSION 3.15)

project(HelloCmake)

add_executable(hello main.cpp)

add_subdirectory(LibAdder)

# get glfw from github
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(STATUS "Find git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

add_subdirectory(thirdparty/GLFW)

target_include_directories(hello 
    PRIVATE LibAdder
    PUBLIC thirdparty/GLFW/include
)

target_link_libraries(hello 
    PRIVATE adder
    PUBLIC glfw
)