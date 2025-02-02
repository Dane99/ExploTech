cmake_minimum_required(VERSION 3.31)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ExploTech)

file(GLOB_RECURSE ExploTech_SRC CONFIGURE_DEPENDS "*.cpp" "*.h")

add_executable(ExploTech ${ExploTech_SRC})

find_package(freetype CONFIG REQUIRED)
target_link_libraries(ExploTech PRIVATE freetype)

find_package(GLEW REQUIRED)
target_link_libraries(ExploTech PRIVATE GLEW::GLEW)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ExploTech PRIVATE glfw)

find_package(SFML 2 COMPONENTS graphics audio network REQUIRED)
target_link_libraries(ExploTech PRIVATE
    sfml-graphics 
    sfml-audio 
    sfml-network
)

find_package(glm CONFIG REQUIRED)
target_include_directories(ExploTech PRIVATE ${GLM_INCLUDE_DIRS})