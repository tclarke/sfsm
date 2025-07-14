/**
 * demo.cpp: Static finite state machine.
 * Unlicensed (see LICENSE)
 */

#include <iostream>
#include "sfsm.h"

enum Events { EVT1, EVT2, EVT3 };

struct printing_cb {
    static void cb(sfsm::state_id_t from, Events evt, sfsm::state_id_t to) {
        std::cout << " [" << from << "," << evt << "," << to << "] ";
    }
};

int main()
{
    sfsm::StateMachine<Events,
        sfsm::State<Events, 1,
            sfsm::transition_t<Events, EVT1, 2>,
            sfsm::transition_t<Events, EVT2, 1, printing_cb>>,
        sfsm::State<Events, 2,
            sfsm::transition_t<Events, EVT3, 1>>> machine(1);
    
    std::cout << machine.cur_state << " -> " << machine(EVT1) << std::endl;  // 1 -> 2
    std::cout << machine.cur_state << " -> " << machine(EVT3) << std::endl;  // 2 -> 1
    std::cout << machine.cur_state << " -> " << machine(EVT2) << std::endl;  // 1 -> 1
    try {
        std::cout << machine.cur_state << " -> " << machine(EVT3) << std::endl;
    } catch (const sfsm::invalid_transition&) {
        std::cout << "Invalid transition!" << std::endl;
    }

    return 0;
}