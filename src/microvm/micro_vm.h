/**
 * micro_vm class declaration
 *
 * @file micro_vm.h
 */
#ifndef MICROVM_MICRO_VM_H
#define MICROVM_MICRO_VM_H

#include <cstdint>
#include <string>

class opcode;

/**
 * simple virtual machine
 */
class micro_vm {
public:
    enum constants {
        reg_count = 16,
        mem_size = 256
    };
    enum FLAGS {
        FEOF, ZERO, HALT
    };

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
     * get register value
     * @param id register id
     * @return register value
     */
    std::uint8_t get_reg(std::size_t);

    /**
     * set register value
     * @param id register id
     * @param value new value
     */
    void set_reg(std::size_t, std::uint8_t);

    /**
     * get flag state
     * @param id flag id
     * @return flag state
     */
    bool get_flag(std::size_t);

    /**
     * get flag state
     * @param id flag id
     * @return flag state
     */
    void set_flag(std::size_t, bool);

    /**
     * increment instruction pointer
     * @param offset address offset
     */
    void inc_ip(int8_t offset);

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
    ~micro_vm();

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
