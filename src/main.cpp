/**
 * mvm project entry point
 *
 * @file main.cpp
 *
 * build command:
 *    g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror main.cpp microvm/micro_vm.cpp microvm/opcode_impl.cpp -o mvm
 * run command
 *    ./mvm program.bin input.txt
 */
#include "microvm/micro_vm.h"
#include "microvm/opcode_impl.h"

#include <iostream>

using namespace std;
/**
 * Create new VM instance, load program and init opcode table
 * @param program_file
 * @param data_file
 * @return new VM instance
 */
micro_vm load_vm(const std::string& program_file, const std::string& data_file);
/**
 * programm entry point
 *
 * @param argc arg count
 * @param argv arg vector
 * @return exit code
 */
int main(int argc, char** argv) {
    if (argc == 3) {
        load_vm(argv[1], argv[2]).run();
    }
    else {
        std::cout << "Usage: " << argv[0] << " program.bin input.txt" << std::endl;
    }
    return 0;
}

micro_vm load_vm(const std::string &program_file, const std::string &data_file) {
    /**
     * VM instance
     */
    micro_vm vm;

    vm.load_prog(program_file);
    // increment
    vm.register_opcode(OPCODES::INC,  new inc_op());
    // decrement
    vm.register_opcode(OPCODES::DEC,  new dec_op());
    // assign
    vm.register_opcode(OPCODES::MOV,  new mov_op ());
    vm.register_opcode(OPCODES::MOVC, new movc_op());
    // shift
    vm.register_opcode(OPCODES::LSL,  new lsl_op());
    vm.register_opcode(OPCODES::LSR,  new lsr_op());
    // jumps
    vm.register_opcode(OPCODES::JMP,  new jmp_op());
    vm.register_opcode(OPCODES::JZ,   new jz_op ());
    vm.register_opcode(OPCODES::JNZ,  new jnz_op());
    vm.register_opcode(OPCODES::JFE,  new jfe_op());
    // halt
    vm.register_opcode(OPCODES::RET,  new ret_op());
    // arithmetic
    vm.register_opcode(OPCODES::ADD,  new add_op());
    vm.register_opcode(OPCODES::SUB,  new sub_op());
    vm.register_opcode(OPCODES::XOR,  new xor_op());
    vm.register_opcode(OPCODES::OR,   new or_op ());
    // IO
    vm.register_opcode(OPCODES::IN,   new in_op (data_file));
    vm.register_opcode(OPCODES::OUT,  new out_op(std::cout));
    return vm;
}
