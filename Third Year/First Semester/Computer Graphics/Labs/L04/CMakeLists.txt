cmake_minimum_required(VERSION 3.29)
project(L04)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DGLEW_STATIC)

add_executable(L04 main.cpp src/loadShaders.cpp src/imageloader.cpp)

target_include_directories(L04
        PRIVATE
        include
        include/GL
        include/glad
        include/GLFW
        include/glm
        include/KHR
        lib/x32
        lib/x64
        lib/x32/GL
        lib/x32/GL/DLLS
        lib/x64/GL
        lib/x64/GL/DLLs
        lib/x32/GLFW
        lib/x64/GLFW
        src
)

find_package(OpenGL REQUIRED)

target_link_libraries(L04
        PRIVATE
        ${OPENGL_LIBRARIES}
        "D:\\UNI CODE\\Univeristy-Work\\Third Year\\First Semester\\Computer Graphics\\Labs\\L04\\lib\\x64\\GL\\glew32s.lib"
        "D:\\UNI CODE\\Univeristy-Work\\Third Year\\First Semester\\Computer Graphics\\Labs\\L04\\lib\\x64\\GL\\freeglut.lib"
        "D:\\UNI CODE\\Univeristy-Work\\Third Year\\First Semester\\Computer Graphics\\Labs\\L04\\lib\\x64\\SOIL\\SOIL.lib"
        opengl32
)