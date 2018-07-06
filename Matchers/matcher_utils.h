//
// Created by Matthias Hölzl on 7/6/2018.
//

#ifndef SIMPLE_PROJECT_MATCHER_UTILS_H
#define SIMPLE_PROJECT_MATCHER_UTILS_H

#include <gmock/gmock-matchers.h>
#include <cassert>

namespace testing {
template<typename T>
class FieldwiseMatcher : public MatcherInterface<T> {
public:
    mutable MatchResultListener* match_result_listener_{nullptr};
    mutable bool first_failure_reason_not_yet_printed{true};

    template<typename T1, typename T2>
    void ReportMismatch(std::string message, T1 lhs, T2 rhs) const {
        if (match_result_listener_) {
            if (first_failure_reason_not_yet_printed) {
                *match_result_listener_ << "\n\n";
            }
            *match_result_listener_ << message << ": " << PrintToString(lhs) << " != " << PrintToString(rhs) << "\n";
            first_failure_reason_not_yet_printed = false;
        }
    }

    template<typename T1, typename T2>
    bool CheckValuesMatch(std::string message, T1 lhs, T2 rhs) const {
        if (lhs == rhs) {
            return true;
        }
        ReportMismatch(message, lhs, rhs);
        return false;
    }

    template<typename T1, typename T2>
    bool CheckFieldsMatch(std::string field, T1 lhs, T2 rhs) const {
        return CheckValuesMatch("Values of field " + field + " do not match", lhs, rhs);
    }

    template<typename T1, typename T2>
    bool CheckFieldsMatch(std::string lhs_field, std::string rhs_field, T1 lhs, T2 rhs) const {
        return CheckValuesMatch("Field " + lhs_field + " does not match field " + rhs_field, lhs, rhs);
    }

    template<typename T1, typename T2>
    bool CheckSubfieldsMatch(std::string accessor, std::string subfield, T1 lhs, T2 rhs) const {
        return CheckValuesMatch("Values of " + accessor + "::" + subfield + " do not match", lhs, rhs);
    }

    template<typename T1, typename T2>
    bool CheckSubfieldsMatch(std::string accessor, std::string lhs_field, std::string rhs_field, T1 lhs, T2 rhs) const {
        return CheckValuesMatch(
                "Field " + accessor + "::" + lhs_field + " does not match field " + accessor + "::" + rhs_field, lhs,
                rhs);
    }

    virtual bool CheckUnitAgainstValuesStoredInMatcher(T unit) const = 0;

    bool MatchAndExplain(T unit, MatchResultListener* listener) const override {
        match_result_listener_ = listener;
        return CheckUnitAgainstValuesStoredInMatcher(unit);
    }

    // Describes this matcher to an ostream.
    void DescribeTo(::std::ostream* os) const override {
        if (os) {
            *os << "Unit matches (using FieldwiseMatcher)" << std::endl;
        }
    };

    // Describes the negation of this matcher to an ostream.
    void DescribeNegationTo(::std::ostream* os) const override {
        if (os) {
            *os << "Unit does not match (using FieldwiseMatcher)" << std::endl;
        }
    }
};

// This is mostly there as an example how a new matcher should be defined.
template<typename T>
inline Matcher<const T&> MatchesFieldsOf(const T& /* expectedValue */) noexcept {
    // return MakeMatcher<T>(new FieldwiseMatcher<T>(expectedValue));
    assert(false);
}
}  // namespace testing

#endif //SIMPLE_PROJECT_MATCHER_UTILS_H
