cmake_minimum_required(VERSION 3.14)
project(LEARNGL VERSION 0.1)



set(SOURCES
    "Lighting.cpp"
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core.cpp
)

find_package (Threads)

add_executable(gl7 ${SOURCES})
target_include_directories(gl7 PUBLIC "./include/")
message(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
target_link_libraries(gl7 ${CMAKE_CURRENT_SOURCE_DIR}/glfw/glfw/build/src/libglfw3.a)
target_link_libraries(gl7 ${CMAKE_DL_LIBS})
target_link_libraries (gl7 ${CMAKE_THREAD_LIBS_INIT})
target_link_directories(gl7 PUBLIC "./src/")