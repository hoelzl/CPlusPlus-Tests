// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//

#include <iostream>
#include <optional>
#include <functional>
#include <numeric>

struct DomainType {
    std::array<int, 512> ints{};

    DomainType() {
        ints.fill(1);
    }
};

std::ostream& operator<<(std::ostream& stream, const DomainType& value) {
    stream << "DomainType: " << value.ints[0];
    return stream;
}


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

void print_value(const DomainType* value);

void int_pointer_proxy_example();

void int_reference_wrapper_proxy_example();

void domain_pointer_proxy_example();

int main() {
    int_pointer_proxy_example();
    int_reference_wrapper_proxy_example();

    domain_pointer_proxy_example();

    return 0;
}

void int_pointer_proxy_example() {
    std::cout << "\n\nPointerProxy<int>\n" << std::endl;
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

void int_reference_wrapper_proxy_example() {
    std::cout << "\n\nReferenceProxy<int>\n" << std::endl;
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

void domain_pointer_proxy_example() {
    std::cout << "\n\nPointerProxy<DomainType>\n" << std::endl;
    PointerProxy<DomainType> proxy{};
    print_value(proxy.Get());

    DomainType value{};
    proxy.Set(value);
    print_value(proxy.Get());
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

void print_value(const DomainType* value) {
    std::cout << "Proxy value (pointer): ";
    if (value) {
        std::cout << *value;
    } else {
        std::cout << "<no value>";
    }
    std::cout << std::endl;
}
