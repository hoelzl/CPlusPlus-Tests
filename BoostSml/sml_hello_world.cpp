// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//
#include <iostream>
#include <boost/sml.hpp>

namespace sml = boost::sml;
using namespace sml;

namespace {

// Define some events.

    struct turn_on {
    };
    struct event2 {
    };
    struct turn_off {
    };
}

struct states {
    static constexpr decltype(sml::state<class idle>) inactive = sml::state<class idle>;

    auto operator()() const noexcept {
        using namespace sml;
//        static const auto idle = state<class idle>;
        return make_transition_table(
                *inactive + event<event1> = "state_1"_s,
                "state_1"_s + sml::on_entry<_> / [] { std::cout << "Entering state_1" << std::endl; },
                "state_1"_s + sml::on_exit<_> / [] { std::cout << "Exiting state_1" << std::endl; },
                "state_1"_s + event<event1> = "state_1"_s,
                "state_1"_s + event<event2> = "state_2"_s,
                "state_2"_s + event<turn_off> = X
        );
    }
};

struct const_states {
    static constexpr decltype(sml::state<class idle>) idle = sml::state<class idle>;
    static constexpr decltype(sml::state<class state_1>) state_1 = sml::state<class state_1>;
    static constexpr decltype(sml::state<class state_22>) state_2 = sml::state<class state_22>;

    auto operator()() const noexcept {
        using namespace sml;
        return make_transition_table(
                *idle + event<event1> = state_1,
                state_1 + sml::on_entry<_> / [] { std::cout << "Entering state_1" << std::endl; },
                state_1 + sml::on_exit<_> / [] { std::cout << "Exiting state_1" << std::endl; },
                state_1 + event<event1> = state_1,
                state_1 + event<event2> = state_2,
                state_2 + event<turn_off> = X,
                X + sml::on_entry<_> / [] { std::cout << "Entering state X" << std::endl; }
        );
    }
};


template<typename S, typename T>
void CheckState(const S &state_machine, const char *state_name, const T &state) {
    std::cout << "State machine is in state " << state_name << ": " << std::boolalpha << state_machine.is(state)
              << std::endl;
}

int main() {
    using namespace sml;

    sml::sm<states> state_machine;

//    CheckState(state_machine, "idle", sml::state<class idle>);
    CheckState(state_machine, "idle", sml::state<class idle>);

    state_machine.process_event(turn_on{});
    CheckState(state_machine, "idle", sml::state<class idle>);
    CheckState(state_machine, "idle", "state_1"_s);

    state_machine.process_event(turn_on{});
    state_machine.process_event(event2{});
    state_machine.process_event(turn_off{});

    CheckState(state_machine, "X", sml::X);

    std::cout << std::endl;

    sml::sm<const_states> const_state_machine;
    CheckState(const_state_machine, "idle", const_states::idle);

    const_state_machine.process_event(turn_on{});

    CheckState(const_state_machine, "idle", const_states::idle);
    CheckState(const_state_machine, "state_1", const_states::state_1);

    const_state_machine.process_event(turn_on{});
    CheckState(const_state_machine, "state_1", const_states::state_1);

    const_state_machine.process_event(event2{});
    CheckState(const_state_machine, "state_2", const_states::state_2);
    CheckState(const_state_machine, "state_2", state<class state_22>);

    const_state_machine.process_event(turn_off{});
    CheckState(const_state_machine, "X", sml::X);

    return 0;
}