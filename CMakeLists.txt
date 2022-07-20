cmake_minimum_required(VERSION 3.15)

project(HelloCmake VERSION 1.1)

add_executable(hello main.cpp)


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


option(USE_ADDER "a library for adding two float number" ON)
option(USE_GLFW "USE GLFW" ON)

if(USE_ADDER)
    list(APPEND EXTRA_INCLUDE_DIRS LibAdder)
    list(APPEND EXTRA_LIB_LINK_DIRS ${PROJECT_BINARY_DIR}/LibAdder)
    list(APPEND EXTRA_LIBS adder)
endif()

if(USE_GLFW)
    list(APPEND EXTRA_INCLUDE_DIRS ThirdParty/GLFW/include)
    list(APPEND EXTRA_LIB_LINK_DIRS ${PROJECT_BINARY_DIR}/ThirdParty/GLFW/src)
    list(APPEND EXTRA_LIBS glfw3)
endif()

configure_file(HelloCmakeConfig.h.in ./config/HelloCmakeConfig.h)

target_include_directories(hello
    PRIVATE ${PROJECT_BINARY_DIR}/config
    PUBLIC ${EXTRA_INCLUDE_DIRS}
)

target_link_directories(hello 
    PUBLIC ${EXTRA_LIB_LINK_DIRS}
    )

target_link_libraries(hello PUBLIC ${EXTRA_LIBS})