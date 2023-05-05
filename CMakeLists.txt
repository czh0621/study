cmake_minimum_required(VERSION 3.20)
project(tuturial)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(./memory_assign memory_assign_src)
aux_source_directory(./virtual_class virtual_class_src)
aux_source_directory(./smart_ptr smart_ptr_src)
add_executable(s_memory test_memory.cpp ${memory_assign_src} ${virtual_class_src})
add_executable(s_smart_prt test_smart_ptr.cpp ${smart_ptr_src})