cmake_minimum_required(VERSION 3.14)
project(LEARNGL VERSION 0.1)

set(PNAME Model-Loader)

set(SOURCES
    "loadMesh.cpp"
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/Core.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/Engine/object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Model.cpp
    

)

find_package (Threads)

add_executable(${PNAME} ${SOURCES})
target_include_directories(${PNAME} PUBLIC "./include/" "./include/Engine/")
message(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

if (WIN32)
    target_link_libraries(${PNAME} ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/glfw3.lib)

elseif(UNIX)
    target_link_libraries(${PNAME} ${CMAKE_CURRENT_SOURCE_DIR}/glfw/glfw/build/src/libglfw3.a)
    target_link_libraries(${PNAME} ${CMAKE_CURRENT_SOURCE_DIR}/include/assimp/libassimp.so)

endif()
target_link_libraries(${PNAME} ${CMAKE_DL_LIBS})
target_link_libraries (${PNAME} ${CMAKE_THREAD_LIBS_INIT})
# target_link_directories(${PNAME} PUBLIC "./src/")