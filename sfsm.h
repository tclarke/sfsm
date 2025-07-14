/**
 * sfsm.h: Static finite state machine.
 * Unlicensed (see LICENSE)
 */

#pragma once
#ifndef SFSM_H__
#define SFSM_H__

#include <functional>
#include <tuple>

namespace sfsm
{

struct invalid_transition : public std::exception {};
using state_id_t = int;

template<typename EVENT_T, EVENT_T E, state_id_t S>
struct transition_t {
    static constexpr EVENT_T event = E;
    static constexpr state_id_t next_state = S;
};

template<typename EVENT_T, state_id_t ID, typename...TRS>
struct State {
    static constexpr state_id_t state_id = ID;
    static state_id_t next(const EVENT_T& evt) { throw invalid_transition(); }
};

template<typename EVENT_T, state_id_t ID, typename TR, typename...TRS>
struct State<EVENT_T, ID, TR, TRS...> {
    static constexpr state_id_t state_id = ID;
    static state_id_t next(const EVENT_T& evt) {
        if (TR::event == evt) {
            return TR::next_state;
        }
        return State<EVENT_T, ID, TRS...>::next(evt);
    }
};

template<typename EVENT_T, typename...STATES>
struct StateMachine
{
    constexpr explicit StateMachine(const state_id_t initial_state) : cur_state(initial_state) {}

    state_id_t operator()(const EVENT_T& evt)
    {
        throw invalid_transition();
    }

    state_id_t cur_state;
};

template<typename EVENT_T, typename STATE, typename... STATES>
struct StateMachine<EVENT_T, STATE, STATES...>
{
    state_id_t operator()(const EVENT_T& evt)
    {
        if (cur_state == STATE::state_id)
        {
            cur_state = STATE::next(evt);
        }
        else
        {
            StateMachine<EVENT_T, STATES...> tmp(cur_state);
            cur_state = tmp(evt);
        }
        return cur_state;
    }

    constexpr explicit StateMachine(const state_id_t initial_state) : cur_state(initial_state) {}

    state_id_t cur_state;
};

}

#endif