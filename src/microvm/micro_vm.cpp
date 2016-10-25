/**
 * micro_vm class realisation
 *
 * @file micro_vm.cpp
 */

#include "micro_vm.h"
#include "opcode.h"

#include <utility>
#include <map>
#include <memory>
#include <fstream>
#include <iostream>

/**
 * VM state
 */
struct micro_vm::vm_state {
    using opcode_map = std::map<std::uint8_t, std::unique_ptr<opcode>>;

    /**
     * instruction pointer
     */
    std::size_t ip;

    /**
     * flags register
     */
    std::uint8_t flags;

    /**
     * common registers
     */
    std::uint8_t reg[micro_vm::reg_count];

    /**
     * program memory
     */
    std::int8_t mem[micro_vm::mem_size];

    /**
     * opcode table
     */
    opcode_map op;

    /**
     * constructor
     */
    vm_state() : ip{0}, flags{0}, reg{0}, mem{0}, op{} {}
};

micro_vm::micro_vm() : self(new vm_state) {}

micro_vm::~micro_vm() {
    if (self) {
        delete self;
    }
}

void micro_vm::register_opcode(std::uint8_t code, opcode *op) {
    self->op[code].reset(op);
}

bool micro_vm::stopped() { return get_flag(HALT); }

std::uint8_t micro_vm::get_reg(std::size_t id) {
    return self->reg[id];
}

void micro_vm::set_reg(std::size_t id, std::uint8_t value) {
    self->reg[id] = value;
    set_flag(micro_vm::ZERO, value == 0);
}

bool micro_vm::get_flag(std::size_t id) {
    return (self->flags & (1u << id)) != 0;
}

void micro_vm::set_flag(std::size_t id, bool flag) {
    // "magic of bits" )
    uint8_t mask = uint8_t((1u << id) & 0xffu);
    // clear bit at flag position
    self->flags ^= self->flags & mask;
    if (flag) {
        // set up bit at flag position
        self->flags |= mask;
    }
}

void micro_vm::do_step() {
    // get current opcode
    uint8_t code = uint8_t(self->mem[self->ip] & 0xffu);
    // find handler
    auto op = self->op.find(code);
    if (std::end(self->op) == op) {
        throw std::runtime_error("unknown opcode " + std::to_string(code));
    }
    // call handler
    op->second->process(this, self->mem[self->ip + 1]);
}

void micro_vm::run() {
    while (!stopped()) {
        do_step();
    }
}

void micro_vm::inc_ip(int8_t offset) {
    // range check
    {
        ssize_t ip = self->ip + offset;
        if (ip < 0 || ip >= mem_size) {
            throw std::runtime_error(
                    "offset "+std::to_string(offset)+" outside memory. unable move to " + std::to_string(ip)
            );
        }
    }
    // move pointer
    self->ip += offset;
}

void micro_vm::load_prog(const std::string &name) {
    std::ifstream in;

    // open file as binary
    in.open(name, std::ios::binary | std::ios::in);
    in.readsome((char *) self->mem, mem_size);
}

micro_vm &micro_vm::operator=(micro_vm &&vm) {
    std::swap(self, vm.self);
    return *this;
}

micro_vm::micro_vm(micro_vm &&vm) : self(nullptr) {
    std::swap(self, vm.self);
}
