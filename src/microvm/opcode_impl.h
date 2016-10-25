/**
 * concrete opcode handlers declaration
 *
 * @file opcode_impl.h
 */
#ifndef MICROVM_OPCODE_IMPL_H
#define MICROVM_OPCODE_IMPL_H

#include "opcode.h"
#include "micro_vm.h"
#include <fstream>
#include <ostream>

/**
 * Opcode constants
 */
enum OPCODES {
    /*
    code =  hex, // params  // comment
    */
    INC  = 0x01, // Rx      // Rx = Rx + 1
    DEC  = 0x02, // Rx      // Rx = Rx - 1
    MOV  = 0x03, // Rx, Ry  // Rx = Ry
    MOVC = 0x04, // "const" // R0 = "const"
    LSL  = 0x05, // Rx      // Rx = Rx << 1;
    LSR  = 0x06, // Rx      // Rx = Rx >> 1;
    JMP  = 0x07, // addr    // ip += addr
    JZ   = 0x08, // addr    // ip += addr if flag == 0
    JNZ  = 0x09, // addr    // ip += addr if flag != 0
    JFE  = 0x0A, // addr    // ip += addr if eof(data)
    RET  = 0x0B, //         // halt VM
    ADD  = 0x0C, // Rx, Ry  // Rx = Rx + Ry
    SUB  = 0x0D, // Rx, Ry  // Rx = Rx - Ry
    XOR  = 0x0E, // Rx, Ry  // Rx = Rx xor Ry
    OR   = 0x0F, // Rx, Ry  // Rx = Rx bit_or Ry
    IN   = 0x10, // Rx      // read byte from input
    OUT  = 0x11, // Rx
};

/**
 * dummy opcode
 */
class unimplemented : public opcode {
public:
    unimplemented(OPCODES code);

    /**
     * throws "unimplemented" exception when called
     * @param vm unused
     * @param data unused
     */
    void process(micro_vm *, std::int8_t) override;

private:
    OPCODES code;
};

/**
 * increment
 */
class inc_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * decrement
 */
class dec_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * assign
 */
class mov_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * assign R0 t0 const value
 */
class movc_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data constant
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * left shift
 */
class lsl_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * right shift
 */
class lsr_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * jump
 */
class jmp_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data addres shift
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * jump if zero flag is set
 */
class jz_op : public jmp_op {
public:
    /**
     * @param vm virtual machine
     * @param data addres shift
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * jump if zero flag is not set
 */
class jnz_op : public jmp_op {
public:
    /**
     * @param vm virtual machine
     * @param data addres shift
     */
    void process(micro_vm *, std::int8_t) override;
};

/**
 * jump if eof flag is set
 */
class jfe_op : public jmp_op {
public:
    /**
     * @param vm virtual machine
     * @param data addres shift
     */
    void process(micro_vm *, std::int8_t) override;
};
/**
 * halt VM
 */
class ret_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data unused
     */
    void process(micro_vm *vm, std::int8_t) override;
};

/**
 * Rx += Ry
 */
class add_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *vm, std::int8_t) override;
};

/**
 * Rx -= Ry
 */
class sub_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *vm, std::int8_t) override;
};

/**
 * Rx ^= Ry
 */
class xor_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *vm, std::int8_t) override;
};

/**
 * Rx |= Ry
 */
class or_op : public opcode {
public:
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *vm, std::int8_t) override;
};

/**
 * read byte from data stream
 */
class in_op : public opcode {
public:
    /**
     * constructor
     * @param in input file name
     */
    in_op(const std::string&);
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *vm, std::int8_t) override;
private:
    /**
     * input stream
     */
    std::ifstream in;
};

/**
 * print byte to output stream
 */
class out_op : public opcode {
public:
    /**
     * constructor
     * @param out output stream
     */
    out_op(std::ostream& out);
    /**
     * @param vm virtual machine
     * @param data 2 packed register id
     */
    void process(micro_vm *vm, std::int8_t) override;
private:
    /**
     * output stream
     */
    std::ostream& out;
};

#endif //MICROVM_OPCODE_IMPL_H
