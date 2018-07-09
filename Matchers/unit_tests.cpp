// Copyright 2018 Dr. Matthias Hölzl
// Licensed under the MIT License
//

#include "lib.h"
#include "matcher_utils.h"
#include "gmock/gmock.h"

using ::testing::Eq;
using ::testing::DoubleEq;
using ::testing::FieldwiseMatcher;
using ::testing::Matcher;
using ::testing::MatchesFieldsOf;

struct Foo {
    int my_int{0};
    std::string my_string{"Foo foo!"};
};

class FooMatcher : public FieldwiseMatcher<const Foo&> {
public:
    FooMatcher(const Foo& expected_result) : expected_result_{expected_result} {
    }

    Foo expected_result_;

    bool CheckUnitAgainstValuesStoredInMatcher(const Foo& unit) const override {
        bool result{true};
        result &= CheckFieldsMatch("my_int", expected_result_.my_int, unit.my_int);
        result &= CheckFieldsMatch("my_string", expected_result_.my_string, unit.my_string);
        return result;
    }

};

template<>
inline Matcher<const Foo&> testing::MatchesFieldsOf(const Foo& foo) noexcept {
    return MakeMatcher<const Foo&>(new FooMatcher(foo));
}

struct Bar {
    Foo your_foo{};
    Foo* your_foo_ptr{nullptr};
};

class BarMatcher : public FieldwiseMatcher<const Bar&> {
public:
    BarMatcher(const Bar& expected_result) : expected_result_{expected_result} {
    }

    Bar expected_result_;

    bool CheckUnitAgainstValuesStoredInMatcher(const Bar& unit) const override {
        bool result{true};
        result &= CheckSubfieldsMatch("your_foo", "my_int", expected_result_.your_foo.my_int, unit.your_foo.my_int);
        result &= CheckSubfieldsMatch("your_foo", "my_string", expected_result_.your_foo.my_string,
                                      unit.your_foo.my_string);
        result &= CheckFieldsMatch("your_foo_ptr", expected_result_.your_foo_ptr, unit.your_foo_ptr);
        return result;
    }

};


template<>
inline Matcher<const Bar&> testing::MatchesFieldsOf(const Bar& bar) noexcept {
    return MakeMatcher<const Bar&>(new BarMatcher(bar));
}

struct Quux {
    Foo his_foo{};
    Foo* his_foo_ptr{nullptr};
};

class QuuxMatcher : public FieldwiseMatcher<const Quux&> {
public:
    QuuxMatcher(const Bar& expected_result) : expected_result_{expected_result} {}

    Bar expected_result_;


    bool CheckUnitAgainstValuesStoredInMatcher(const Quux& unit) const override {
        bool result{true};
        result &= CheckFieldsMatch("your_foo::my_int", "his_foo::my_int", expected_result_.your_foo.my_int,
                                   unit.his_foo.my_int);
        result &= CheckFieldsMatch("your_foo::my_string", "his_foo::my_string", expected_result_.your_foo.my_string,
                                   unit.his_foo.my_string);
        result &= CheckFieldsMatch("your_foo_ptr", "his_foo_ptr", expected_result_.your_foo_ptr, unit.his_foo_ptr);
        return result;
    }
};

inline Matcher<const Quux&> MatchesFieldsOfBar(const Bar& bar) noexcept {
    return testing::MakeMatcher<const Quux&>(new QuuxMatcher(bar));
}

TEST(FooTest, Successful) {
    Foo foo{};
    EXPECT_THAT(foo, MatchesFieldsOf(foo));
}

TEST(FooTest, SuccessfulToo) {
    Foo foo{};
    Foo bar{};
    EXPECT_THAT(foo, MatchesFieldsOf(bar));
}

TEST(FooTest, Failing) {
    Foo foo{};
    Foo bar{1, "Who, me?"};
    EXPECT_THAT(foo, MatchesFieldsOf(bar));
}


TEST(BarTest, Successful) {
    Bar bar{};
    EXPECT_THAT(bar, MatchesFieldsOf(bar));
}

TEST(BarTest, SuccessfulToo) {
    Bar bar{};
    Bar baz{};
    EXPECT_THAT(bar, MatchesFieldsOf(baz));
}

TEST(BarTest, Failing) {
    Foo foo{42, "Oh noes!"};
    Bar bar{};
    Bar baz{foo, &foo};
    EXPECT_THAT(bar, MatchesFieldsOf(baz));
}


TEST(QuuxTest, Successful) {
    Bar bar{};
    Quux quux{};
    EXPECT_THAT(quux, MatchesFieldsOfBar(bar));
}


TEST(QuuxTest, SuccessfulToo) {
    Foo foo{42, "Woo hoo!"};
    Bar bar{foo, &foo};
    Quux quux{foo, &foo};
    EXPECT_THAT(quux, MatchesFieldsOfBar(bar));
}

TEST(QuuxTest, Failing) {
    Foo foo{42, "Woo hoo!"};
    Bar bar{foo, &foo};
    Quux quux{};
    EXPECT_THAT(quux, MatchesFieldsOfBar(bar));
}

TEST(QuuxTest, FailingToo) {
    Foo foo{42, "Woo hoo!"};
    Bar bar{};
    Quux quux{foo, &foo};
    EXPECT_THAT(quux, MatchesFieldsOfBar(bar));
}
