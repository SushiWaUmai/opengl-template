cmake_minimum_required(VERSION 3.0)

project(learn_opengl C)

add_subdirectory("./deps/glad")

add_subdirectory("./deps/glfw")
include_directories("./deps/glfw/include")

add_compile_options("-lglad" "-lglfw3")

add_executable(learn_opengl "src/main.c" "src/file_loader.c" "src/file_loader.h")
target_link_libraries(learn_opengl "glad" "glfw")

add_custom_target("copy-assets-folder" ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)