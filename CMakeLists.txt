cmake_minimum_required(VERSION 3.10)

option(DTV "Enable video output" OFF)

if (DTV)
    add_compile_definitions(ATG_SCS_DEMO_ENABLE_VIDEO_CAPTURE)
ENDIF (DTV)

# Enable group projects in folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(scs-2d-demo)

set(CMAKE_CXX_STANDARD 20)

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
    src/rolling_constraint.cpp
    src/rolling_demo.cpp
    src/double_pendulum_demo.cpp
    src/empty_object.cpp
    src/energy_transfer_demo.cpp
    src/plotter.cpp
    src/spring_mass_demo.cpp
    src/spring_cloth_demo.cpp
    src/blob.cpp
    src/blob_force.cpp
    src/blob_game_demo.cpp
    src/spring_double_pendulum_demo.cpp
    src/triple_pendulum_demo.cpp
    src/complex_roller_demo.cpp
    src/constant_rotation_constraint.cpp

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
    include/rolling_constraint.h
    include/rolling_demo.h
    include/empty_object.h
    include/energy_transfer_demo.h
    include/plotter.h
    include/spring_mass_demo.h
    include/spring_cloth_demo.h
    include/blob.h
    include/blob_force.h
    include/blob_game_demo.h
    include/spring_double_pendulum_demo.h
    include/triple_pendulum_demo.h
    include/complex_roller_demo.h
    include/dtv.h
    include/constant_rotation_constraint.h
)

target_link_libraries(scs-2d-demo
    simple-2d-constraint-solver
    delta-basic)

if (DTV)
    target_link_libraries(scs-2d-demo
        direct-to-video)
endif (DTV)

target_include_directories(scs-2d-demo
    PUBLIC dependencies/submodules)

add_subdirectory(dependencies)

# Application packaging
add_custom_target(scs_2d_demo_copy_resources ALL
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/workspace
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/workspace/builds
                    COMMAND ${CMAKE_COMMAND} -E rm -r -f ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo/bin
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo/basic
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo/basic/fonts
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${CMAKE_SOURCE_DIR}/dependencies/submodules/delta-studio/engines/basic/fonts/Silkscreen
                            ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo/basic/fonts/Silkscreen
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${CMAKE_SOURCE_DIR}/assets
                            ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo/assets
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${CMAKE_SOURCE_DIR}/resources/packaging/bin
                            ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo/bin
                    COMMENT "Packaging game folder")

add_custom_target(ses_copy_exe ALL
                    COMMAND ${CMAKE_COMMAND} -E copy
                            $<TARGET_FILE:scs-2d-demo>
                            ${CMAKE_SOURCE_DIR}/workspace/builds/scs-2d-demo/bin
                    COMMENT "Copying game executable")

add_dependencies(ses_copy_exe scs-2d-demo scs_2d_demo_copy_resources)
