// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//

#include <iostream>
#include <optional>
#include <functional>

template<typename T>
class ReferenceProxy {
public:
    std::optional<std::reference_wrapper<T>> Get() {
        return is_valid_ ? std::optional{std::reference_wrapper{value_}} : std::nullopt;
    }
    std::optional<std::reference_wrapper<const T>> Get() const {
        return is_valid_ ? std::optional{std::reference_wrapper{value_}} : std::nullopt;
    }
    void Set(const T& new_value) {
        value_ = new_value;
        is_valid_ = true;
    }

private:
    bool is_valid_{false};
    T value_{};
};


void print_values(const std::optional<int>& value);

int main() {
    ReferenceProxy<int> ref_proxy{};
    print_values(ref_proxy.Get());
    ref_proxy.Set(1);
    print_values(ref_proxy.Get());
    std::optional<int> value{ ref_proxy.Get() };
    print_values(value);

    ReferenceProxy<int> shadowed_proxy{};
    const ReferenceProxy<int>& const_proxy{shadowed_proxy};
    print_values(const_proxy.Get());
    shadowed_proxy.Set(123);
    print_values(const_proxy.Get());

    return 0;
}

void print_values(const std::optional<int>& value) {
    std::cout << "Proxy value: "
              << (value.has_value() ? std::to_string(value.value()) : "<no value>")
              << std::endl;
}
