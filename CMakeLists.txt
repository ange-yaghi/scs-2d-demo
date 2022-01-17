cmake_minimum_required(VERSION 3.10)

# Enable group projects in folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(scs-2d-demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(scs-2d-demo WIN32
    # Source files
    src/main.cpp

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
    src/constant_speed_motor.cpp
    src/motor_demo.cpp
    src/fixed_position_constraint.cpp
    src/mechanism_demo.cpp
    src/rolling_constraint.cpp
    src/rolling_demo.cpp
    src/double_pendulum_demo.cpp
    src/empty_object.cpp

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
    include/line_constraint.h
    include/constant_speed_motor.h
    include/motor_demo.h
    include/fixed_position_constraint.h
    include/mechanism_demo.h
    include/rolling_constraint.h
    include/rolling_demo.h
    include/empty_object.h
)

target_link_libraries(scs-2d-demo
    simple-2d-constraint-solver
    delta-basic)

target_include_directories(scs-2d-demo
    PUBLIC dependencies/submodules)

add_subdirectory(dependencies)
