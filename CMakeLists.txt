project(mvm)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC_LIST
        src/main.cpp
        src/microvm/micro_vm.cpp
        src/microvm/micro_vm.h
        src/microvm/opcode.h
        src/microvm/opcode_impl.h
        src/microvm/opcode_impl.cpp
        )
add_executable(${PROJECT_NAME} ${SRC_LIST})

configure_file(vm_test/decryptor.bin ${CMAKE_BINARY_DIR}/decryptor.bin COPYONLY)
configure_file(vm_test/q1_encr.txt   ${CMAKE_BINARY_DIR}/q1_encr.txt   COPYONLY)
