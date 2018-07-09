// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//

#include <iostream>
#include <optional>
#include <functional>

template<typename T>
class PointerProxy {
public:
    T* Get() { return is_valid_ ? &value_ : nullptr; }

    const T* Get() const { return is_valid_ ? &value_ : nullptr; }

    void Set(const T& new_value) {
        value_ = new_value;
        is_valid_ = true;
    }

private:
    bool is_valid_{false};
    T value_{};
};

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


void print_value(const std::optional<int>& value);

void print_value(const int* value);

void pointer_proxy_example();

void reference_wrapper_proxy_example();

int main() {
    pointer_proxy_example();
    reference_wrapper_proxy_example();

    return 0;
}

void pointer_proxy_example() {
    PointerProxy<int> pointer_proxy{};
    print_value(pointer_proxy.Get());
    pointer_proxy.Set(1);
    print_value(pointer_proxy.Get());
    int* value{pointer_proxy.Get()};
    print_value(value);

    PointerProxy<int> shadowed_proxy{};
    const PointerProxy<int>& const_proxy{shadowed_proxy};
    print_value(const_proxy.Get());
    shadowed_proxy.Set(123);
    print_value(const_proxy.Get());
}

void reference_wrapper_proxy_example() {
    ReferenceProxy<int> ref_proxy{};
    print_value(ref_proxy.Get());
    ref_proxy.Set(1);
    print_value(ref_proxy.Get());
    std::optional<int> value{ref_proxy.Get()};
    print_value(value);

    ReferenceProxy<int> shadowed_proxy{};
    const ReferenceProxy<int>& const_proxy{shadowed_proxy};
    print_value(const_proxy.Get());
    shadowed_proxy.Set(123);
    print_value(const_proxy.Get());
}

void print_value(const std::optional<int>& value) {
    std::cout << "Proxy value (optional): "
              << (value.has_value() ? std::to_string(value.value()) : "<no value>")
              << std::endl;
}

void print_value(const int* value) {
    std::cout << "Proxy value (pointer): "
              << (value ? std::to_string(*value) : "<no value>")
              << std::endl;
}
