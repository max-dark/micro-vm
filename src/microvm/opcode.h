/**
 * opcode interface declaration
 *
 * @file opcode.h
 */
#ifndef MICROVM_OPCODE_H
#define MICROVM_OPCODE_H

#include <cstdint>

class micro_vm;

/**
 * VM opcode interface
 */
class opcode {
public:
    /**
     * @param vm VM instance
     * @param data opcode parameters
     */
    virtual void process(micro_vm *, std::int8_t) = 0;
};

#endif //MICROVM_OPCODE_H
