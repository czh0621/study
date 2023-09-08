cmake_minimum_required(VERSION 3.20)
project(tutorial)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -std=c++14 -w -lpthread -o3")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/product/bin)

aux_source_directory(./memory_assign memory_assign_src)
aux_source_directory(./virtual_class virtual_class_src)
aux_source_directory(./smart_ptr smart_ptr_src)


add_executable(s_memory test_memory.cpp ${memory_assign_src} ${virtual_class_src})
add_executable(s_smart_ptr test_smart_ptr.cpp ${smart_ptr_src})
add_executable(s_template test_template.cpp)
add_executable(s_thread test_thread.cpp)

add_subdirectory(proto)

add_subdirectory(echo_socket)
