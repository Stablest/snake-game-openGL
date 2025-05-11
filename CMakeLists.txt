# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

cmake_minimum_required(VERSION 3.8)
# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(SnakeGameOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

# Find the glfw3 library
find_library(GLFW_LIB glfw3 PATHS ${PROJECT_SOURCE_DIR}/third-parties)
if (NOT GLFW_LIB)
    message(FATAL_ERROR "Could not find GLFW library!")
else()
    message(STATUS "Found GLFW library at ${GLFW_LIB}")
endif()

add_executable(SnakeGameOpenGL src/main.cpp)

target_link_libraries(SnakeGameOpenGL PRIVATE ${GLFW_LIB})
target_include_directories(SnakeGameOpenGL
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)
