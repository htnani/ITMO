cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
project(entranse_task)

include_directories(/Users/sigma/code/ITMO/course_4/io_systems/lib/systemc-2.3.1a/include) # Set your include path from lib here if version is not 2.3.1a
set(SOURCE_FILES
        src/main.cpp

        src/lib/src/core.cpp
        src/lib/include/core.h

        src/lib/include/bus.h
        src/lib/include/addresses.h
        src/lib/include/timer1.h src/lib/include/common.h src/lib/src/timer1.cpp src/lib/src/icconf.cpp src/lib/include/icconf.h src/lib/src/bus.cpp src/lib/include/edge_detector.h src/lib/src/edge_detector.cpp src/lib/include/prescaler.h src/lib/src/prescaler.cpp src/lib/include/buffer.h src/lib/src/buffer.cpp)

add_executable(lab_1 ${SOURCE_FILES})

add_library(systemc_lib STATIC IMPORTED)
set_property(TARGET systemc_lib PROPERTY IMPORTED_LOCATION /Users/sigma/code/ITMO/course_4/io_systems/lib/systemc-2.3.1a/lib-macosx64/libsystemc-2.3.1.dylib) # Set your lib path here
target_link_libraries(lab_1 systemc_lib)