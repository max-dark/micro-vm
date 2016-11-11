#ifndef MVM_ABSTRACT_VM_H
#define MVM_ABSTRACT_VM_H

#include <cstdint>
#include <string>

class abstract_vm {

public:
    enum FLAGS {
        FEOF, ZERO, HALT
    };

    /**
     * get register value
     * @param id register id
     * @return register value
     */
    virtual uint8_t get_reg(std::size_t) = 0;

    /**
     * set register value
     * @param id register id
     * @param value new value
     */
    virtual void set_reg(std::size_t, uint8_t) = 0;

    /**
     * get flag state
     * @param id flag id
     * @return flag state
     */
    virtual bool get_flag(std::size_t) = 0;

    /**
     * get flag state
     * @param id flag id
     * @return flag state
     */
    virtual void set_flag(std::size_t, bool) = 0;

    /**
     * increment instruction pointer
     * @param offset address offset
     */
    virtual void inc_ip(int8_t offset) = 0;

    virtual ~abstract_vm();
};


#endif //MVM_ABSTRACT_VM_H
