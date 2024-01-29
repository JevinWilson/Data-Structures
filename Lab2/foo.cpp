#include "foo.h"

namespace testing {
    // default constructor
    Foo::Foo() : m_intValue(0), m_stringValue("") {}

    // constructor that takes value for both attributes
    Foo::Foo(int intValue, const std::string& stringValue) 
        : m_intValue(intValue), m_stringValue(stringValue) {}
}