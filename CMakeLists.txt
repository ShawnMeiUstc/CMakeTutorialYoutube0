cmake_minimum_required(VERSION 3.15)

SET(VCPKG_ROOT "C:/DevTools/vcpkg")
SET(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
if (DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}")
endif()

project(HelloCmake VERSION 1.1)

message(STATUS "CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

option(USE_ADDER "a library for adding two float number" ON)
option(USE_GLFW "USE GLFW" ON)

if(USE_GLFW)
    #list(APPEND CMAKE_MODULE_PATH "C:\\DevTools\\vcpkg\\installed\\x64-windows\\share\\glfw3")
    find_package(glfw3 CONFIG REQUIRED)
    find_package(glew REQUIRED)
    find_package(OpenGL REQUIRED)
endif()

message(STATUS "CMAKE_PREFIX_PATH : ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")
message(STATUS "${GLEW_DIR}  ${GLFW_DIR}  ${OPENGL_DIR}")


add_executable(hello main.cpp)


# # get glfw from github
# find_package(Git QUIET)

# if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#     message(STATUS "Find git")

#     # Update submodules as needed
#     option(GIT_SUBMODULE "Check submodules during build" ON)

#     if(GIT_SUBMODULE)
#         message(STATUS "Submodule update")
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#             RESULT_VARIABLE GIT_SUBMOD_RESULT)

#         if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#             message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#         endif()
#     endif()
# endif()


if(USE_ADDER)
    add_subdirectory(./LibAdder)
    list(APPEND EXTRA_INCLUDE_DIRS LibAdder)
    list(APPEND EXTRA_LIB_LINK_DIRS ${PROJECT_BINARY_DIR}/LibAdder)
    list(APPEND EXTRA_LIBS adder)
endif()

if(USE_GLFW)
    # add_subdirectory(./ThirdParty/GLFW)
    # list(APPEND EXTRA_INCLUDE_DIRS ThirdParty/GLFW/include)
    # list(APPEND EXTRA_LIB_LINK_DIRS ${PROJECT_BINARY_DIR}/ThirdParty/GLFW/src)
    # list(APPEND EXTRA_LIBS glfw3)
    target_link_libraries(hello PUBLIC glfw GLEW::GLEW OpenGL::GL)
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

#install(TARGETS hello DESTINATION bin CONFIGURATIONS Debug)