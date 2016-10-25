/**
 * concrete opcode handlers realisation
 *
 * @file opcode_impl.h
 */
#include "opcode_impl.h"
#include <stdexcept>

unimplemented::unimplemented(OPCODES code) : code(code) {}

void unimplemented::process(micro_vm *, std::int8_t) {
    throw std::logic_error("not implemented opcode " + std::to_string(code));
}

inline size_t reg1(int8_t data) {
    return data & 0x0fu;
}

inline size_t reg2(int8_t data) {
    return (data & 0xf0u) >> 4;
}

static const int instruction_size = 2;

void ret_op::process(micro_vm *vm, std::int8_t) {
    vm->set_flag(micro_vm::HALT, true);
    vm->inc_ip(instruction_size);
}

const uint8_t one = 1;

void inc_op::process(micro_vm *vm, std::int8_t data) {
    size_t reg = reg1(data);
    vm->set_reg(reg, vm->get_reg(reg) + one);
    vm->inc_ip(instruction_size);
}

void dec_op::process(micro_vm *vm, std::int8_t data) {
    size_t reg = reg1(data);
    vm->set_reg(reg, vm->get_reg(reg) - one);
    vm->inc_ip(instruction_size);
}

void mov_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    size_t r2 = reg2(data);
    vm->set_reg(r1, vm->get_reg(r2));
    vm->inc_ip(instruction_size);
}

void jmp_op::process(micro_vm *vm, std::int8_t data) {
    vm->inc_ip(data);
}

void jz_op::process(micro_vm *vm, std::int8_t data) {
    if (!vm->get_flag(micro_vm::ZERO)) {
        jmp_op::process(vm, data);
    } else {
        jmp_op::process(vm, instruction_size);
    }
}

void jnz_op::process(micro_vm *vm, std::int8_t data) {
    if (vm->get_flag(micro_vm::ZERO)) {
        jmp_op::process(vm, data);
    } else {
        jmp_op::process(vm, instruction_size);
    }
}

void jfe_op::process(micro_vm *vm, std::int8_t data) {
    if (vm->get_flag(micro_vm::FEOF)) {
        jmp_op::process(vm, data);
    } else {
        jmp_op::process(vm, instruction_size);
    }
}

void movc_op::process(micro_vm *vm, std::int8_t data) {
    vm->set_reg(0, uint8_t(data & 0xffu));
    vm->inc_ip(instruction_size);
}

void lsr_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    uint8_t result = vm->get_reg(r1) >> 1;
    vm->set_reg(r1, result);
    vm->inc_ip(instruction_size);
}

void lsl_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    uint8_t result = vm->get_reg(r1) << 1;
    vm->set_reg(r1, result);
    vm->inc_ip(instruction_size);
}

in_op::in_op(const std::string &data) {
    in.open(data);
}

void in_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    char tmp;
    bool eof = in.get(tmp).eof();
    vm->set_reg(r1, uint8_t(tmp & 0xffu));
    vm->set_flag(micro_vm::FEOF, eof);
    vm->inc_ip(instruction_size);
}

out_op::out_op(std::ostream &out) : out(out) {}

void out_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    out << vm->get_reg(r1);
    vm->inc_ip(instruction_size);
}

void add_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    size_t r2 = reg2(data);
    vm->set_reg(r1, vm->get_reg(r1) + vm->get_reg(r2));
    vm->inc_ip(instruction_size);
}

void sub_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    size_t r2 = reg2(data);
    vm->set_reg(r1, vm->get_reg(r1) - vm->get_reg(r2));
    vm->inc_ip(instruction_size);
}

void xor_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    size_t r2 = reg2(data);
    vm->set_reg(r1, vm->get_reg(r1) ^ vm->get_reg(r2));
    vm->inc_ip(instruction_size);
}

void or_op::process(micro_vm *vm, std::int8_t data) {
    size_t r1 = reg1(data);
    size_t r2 = reg2(data);
    vm->set_reg(r1, vm->get_reg(r1) | vm->get_reg(r2));
    vm->inc_ip(instruction_size);
}
