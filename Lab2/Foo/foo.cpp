#include "foo.h"

namespace testing {
    // default constructor
    Foo::Foo() : m_intValue(0), m_stringValue("") {}

    // constructor that takes value for both attributes
    Foo::Foo(int intValue, const std::string& stringValue) 
        : m_intValue(intValue), m_stringValue(stringValue) {}

    // getters
    int Foo::getIntValue() const {
        return m_intValue;
    }

    // getter for string
    std::string Foo::getStringValue() const {
        return m_stringValue;
    }

    // setter for int
    void Foo::setIntValue(int intValue) {
        m_intValue = intValue;
    }

    // setter for string
    void Foo::setStringValue(const std::string& stringValue) {
    m_stringValue = stringValue;
    }

    // operator overload
    std::ostream& operator<<(std::ostream& os, const Foo& foo) {
        os << "<FOO:" << foo.m_intValue << ":" << foo.m_stringValue << ">";
        return os;
    }

}