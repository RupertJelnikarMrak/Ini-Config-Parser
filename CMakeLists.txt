cmake_minimum_required(VERSION 3.25.1)
project(IniConfigParser VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.h")

message(STATUS "Add source files:")
foreach(SRC_FILE IN LISTS SRC)
    message(STATUS "${SRC_FILE}")
    endforeach()
    message(STATUS "")
    
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(IniConfigParser PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)