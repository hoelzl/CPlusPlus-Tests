// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//
#include <iostream>
#include <boost/sml.hpp>

namespace sml = boost::sml;
using namespace sml;

// Define some events.

struct turn_on {
};
struct event2 {
};
struct turn_off {
};

auto PrintMessage(const char *message) {
    return [message] {
        std::cout << "  ++ " << message << std::endl;
    };
}

template<typename S, typename T>
void CheckState(const S &state_machine, const char *state_name, const T &state) {
    std::cout << (state_machine.is(state) ? "  // " : "!!!! ")
              << "State machine is in state " << state_name << ": " << std::boolalpha << state_machine.is(state)
              << std::endl;
}

template<typename S, typename T>
void CheckNotState(const S &state_machine, const char *state_name, const T &state) {
    std::cout << (!state_machine.is(state) ? "  // " : "!!!! ")
              << "State machine is not in state " << state_name << ": " << std::boolalpha << !state_machine.is(state)
              << std::endl;
}

struct states {
    static constexpr const auto inactive = sml::state<class inactive>;
    static constexpr const auto active = sml::state<class active>;

    auto operator()() const noexcept {
        return make_transition_table(
                inactive + sml::on_entry<_> / PrintMessage("Entering state inactive."),
                inactive + sml::on_exit<_> / PrintMessage("Exiting state inactive."),
                active + sml::on_entry<_> / PrintMessage("Entering state active."),
                active + sml::on_exit<_> / PrintMessage("Exiting state active."),

                *inactive + sml::event<turn_on> = active,
                active + sml::event<turn_off> = inactive
        );
    }
};


int main() {
    using namespace sml;

    sml::sm<states> state_machine;

    CheckState(state_machine, "inactive", state<class inactive>);

    state_machine.process_event(turn_on{});
    CheckNotState(state_machine, "inactive", state<class inactive>);
    CheckState(state_machine, "active", state<class active>);

    state_machine.process_event(turn_on{});
    CheckState(state_machine, "active", state<class active>);

    state_machine.process_event(turn_off{});
    CheckState(state_machine, "inactive", state<class inactive>);

    std::cout << std::endl;

    return 0;
}