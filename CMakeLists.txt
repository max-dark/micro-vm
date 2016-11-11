project(mvm)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC_LIST
        src/main.cpp
        src/microvm/abstract_vm.cpp
        src/microvm/abstract_vm.h
        src/microvm/micro_vm.cpp
        src/microvm/micro_vm.h
        src/microvm/opcode.h
        src/microvm/opcode_impl.h
        src/microvm/opcode_impl.cpp
        src/microvm/opcode.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(decryptor src/decryptor.cpp)
configure_file(vm_test/decryptor.bin ${CMAKE_BINARY_DIR}/decryptor.bin COPYONLY)
configure_file(vm_test/q1_encr.txt   ${CMAKE_BINARY_DIR}/q1_encr.txt   COPYONLY)
