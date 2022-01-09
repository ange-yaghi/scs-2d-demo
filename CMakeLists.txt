cmake_minimum_required(VERSION 3.10)

# Enable group projects in folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(scs-2d-demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(scs-2d-demo WIN32
    # Source files
    src/main.cpp
    src/double_pendulum_application.cpp
    src/geometry_generator.cpp
    src/demo_application.cpp

    # Include files
    include/delta.h
    include/double_pendulum_application.h
    include/geometry_generator.h
    include/double_pendulum_application.h
)

target_link_libraries(scs-2d-demo
    simple-2d-constraint-solver
    delta-basic)

target_include_directories(scs-2d-demo
    PUBLIC dependencies/submodules)

add_subdirectory(dependencies)
