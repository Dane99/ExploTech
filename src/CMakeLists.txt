cmake_minimum_required(VERSION 3.17)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

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
target_link_libraries(ExploTech PRIVATE sfml-graphics sfml-audio sfml-network FLAC OpenAL OpenGL Vorbis)

find_package(glm CONFIG REQUIRED)
target_link_libraries(ExploTech PRIVATE glm) 
