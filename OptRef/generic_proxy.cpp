// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//

#include <iostream>
#include <optional>

template<typename T>
T ToPrintable(const T& arg) {
    return arg;
}

template<typename T>
std::string ToPrintable(const std::optional<T>& arg) {
    if (arg.has_value()) {
        return std::to_string(arg.value());
    }
    else {
        return "<no value>";
    }
}

template<typename T, typename Res> class Proxy;

template<typename T, typename Res>
struct ProxyTraits {
    static Res Get(const Proxy<T, Res>* arg) {
        std::cout << "Called Get(contst Proxy<T, Res>*) for type " << typeid(arg).name() << std::endl;
        std::cout << "  Result is: " << ToPrintable(arg->value_) << std::endl;
        std::cout << "  Result type is: " << typeid(arg->value_).name() << std::endl;
        return arg->value_;
    }
    static Res Get(Proxy<T, Res>* arg) {
        std::cout << "Called Get(Proxy<T, Res>*) for type " << typeid(arg).name() << std::endl;
        Res result{};
        std::cout << "  Result is: " << ToPrintable(arg->value_) << std::endl;
        std::cout << "  Result type is: " << typeid(arg->value_).name() << std::endl;
        return arg->value_;
    }
};


template<typename T, typename Res>
struct ProxyTraits<T, Res&> {
    static const Res& Get(const Proxy<T, Res&>* arg) {
        std::cout << "Called Get(contst Proxy<T, Res&>*) for type " << typeid(arg).name() << std::endl;
        const Res& result = arg->value_;
        std::cout << "  Result is: " << result << std::endl;
        std::cout << "  Result type is: " << typeid(result).name() << std::endl;
        return result;
    }
    static Res& Get(Proxy<T, Res&>* arg) {
        std::cout << "Called Get(Proxy<T, Res&>*) for type " << typeid(arg).name() << std::endl;
        Res& result = arg->value_;
        std::cout << "  Result is: " << result << std::endl;
        std::cout << "  Result type is: " << typeid(result).name() << std::endl;
        return result;
    }
};


template<typename T, typename Res = T>
class Proxy {
public:
    decltype(auto) Get() {
        return ProxyTraits<T, Res>::Get(this);
    }

    decltype(auto) Get() const {
        return ProxyTraits<T, Res>::Get(this);
    }

    void Set(const T& new_value) {
        std::cout << "Setting new value: " << ToPrintable(new_value) << std::endl;
        value_ = new_value;
        std::cout << "Value is now: " << ToPrintable(value_) << std::endl;
    }

private:
    T value_{};
    friend class ProxyTraits<T, Res>;
};

int main() {
    std::cout << "\n\nInt Proxy:" << std::endl;
    Proxy<int> int_proxy{};
    auto result = int_proxy.Get();

    std::cout << "\n\nConst Int Proxy:" << std::endl;
    const Proxy<int> const_int_proxy{};
    int const_int_result = const_int_proxy.Get();
    const_int_result = 2;
    const_int_proxy.Get();

    std::cout << "\n\nInt Ref Proxy:" << std::endl;
    Proxy<int, int&> int_ref_proxy{};
    int& result_ref = int_ref_proxy.Get();
    result_ref = 10;
    int_ref_proxy.Get();
    int_ref_proxy.Set(20);
    int_ref_proxy.Get();

    std::cout << "\n\nConst Int Ref Proxy:" << std::endl;
    const Proxy<int, int&> const_int_ref_proxy{};
    const int& const_result_ref = const_int_ref_proxy.Get();
    // const_result_ref = 20;
    // const_int_ref_proxy.Get();

    std::cout << "\n\nOptional Int Proxy:" << std::endl;
    Proxy<std::optional<int>> opt_int_proxy{};
    auto optional_int_result = opt_int_proxy.Get();
    opt_int_proxy.Set(30);
    opt_int_proxy.Get();

    std::cout << "\n\nConst Optional Int Proxy:" << std::endl;
    const Proxy<int> const_optional_int_proxy;
    std::optional<int> const_optional_int_result = const_optional_int_proxy.Get();
    const_optional_int_result = 2;
    const_optional_int_proxy.Get();
}
