/**
 * opcode interface declaration
 *
 * @file opcode.h
 */
#ifndef MICROVM_OPCODE_H
#define MICROVM_OPCODE_H

#include <cstdint>
#include "abstract_vm.h"


/**
 * VM opcode interface
 */
class opcode {
public:
    /**
     * @param vm VM instance
     * @param data opcode parameters
     */
    virtual void execute(abstract_vm *vm, std::int8_t data) = 0;

    /**
     * destructor
     */
    virtual ~opcode();
};

#endif //MICROVM_OPCODE_H
