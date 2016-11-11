/**
 * micro_vm class declaration
 *
 * @file micro_vm.h
 */
#ifndef MICROVM_MICRO_VM_H
#define MICROVM_MICRO_VM_H

#include <cstdint>
#include <string>
#include "abstract_vm.h"

#include "opcode.h"

/**
 * simple virtual machine
 */
class micro_vm : public abstract_vm {
public:
    enum constants {
        reg_count = 16,
        mem_size = 256
    };

    /**
     * get register value
     * @param id register id
     * @return register value
     */
    virtual uint8_t get_reg(std::size_t) override;

    /**
     * set register value
     * @param id register id
     * @param value new value
     */
    virtual void set_reg(std::size_t, uint8_t) override;

    /**
     * get flag state
     * @param id flag id
     * @return flag state
     */
    virtual bool get_flag(std::size_t) override;

    /**
     * get flag state
     * @param id flag id
     * @return flag state
     */
    virtual void set_flag(std::size_t, bool) override;

    /**
     * increment instruction pointer
     * @param offset address offset
     */
    virtual void inc_ip(int8_t offset) override;

    /**
     * register opcode pair(code -> handler)
     * @param code binary code for command
     * @param op command handler
     */
    void register_opcode(std::uint8_t, opcode *);

    /**
     * @return "halt" flag value
     */
    bool stopped();

    /**
     * process current opcode
     */
    void do_step();

    /**
     * main loop
     */
    void run();

    /**
     * read program from file
     * @param file program file name
     */
    void load_prog(const std::string &);

    /**
     * default constructor
     */
    micro_vm();

    /**
     * "move" constructor
     */
    micro_vm(micro_vm &&vm);

    /**
     * "move" assigment
     */
    micro_vm &operator=(micro_vm &&vm);

    /**
     * disable copy
     */
    micro_vm(micro_vm &) = delete;

    /**
     * disable copy
     */
    micro_vm &operator=(const micro_vm &) = delete;

    /**
     * destructor
     */
    virtual ~micro_vm();

private:
    /**
     * VM state
     */
    struct vm_state;
    /**
     * VM data
     */
    vm_state *self;
};


#endif //MICROVM_MICRO_VM_H
