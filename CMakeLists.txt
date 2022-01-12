cmake_minimum_required(VERSION 3.10)

# Enable group projects in folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(scs-2d-demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(scs-2d-demo WIN32
    # Source files
    src/main.cpp
    src/double_pendulum_demo.cpp
    src/geometry_generator.cpp
    src/demo_application.cpp
    src/demo.cpp
    src/demo_object.cpp
    src/bar_object.cpp
    src/gravity_object.cpp
    src/link_constraint.cpp
    src/spring_object.cpp
    src/disk_object.cpp
    src/line_constraint.cpp

    # Include files
    include/delta.h
    include/double_pendulum_demo.h
    include/geometry_generator.h
    include/demo.h
    include/demo_application.h
    include/demo_object.h
    include/bar_object.h
    include/gravity_object.h
    include/link_constraint.h
    include/spring_object.h
    include/disk_object.h
    include/line_constraint
)

target_link_libraries(scs-2d-demo
    simple-2d-constraint-solver
    delta-basic)

target_include_directories(scs-2d-demo
    PUBLIC dependencies/submodules)

add_subdirectory(dependencies)
