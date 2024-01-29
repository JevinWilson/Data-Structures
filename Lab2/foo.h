#ifndef FOO_H
#define FOO_H

#include <string>

namespace testing {

class Foo {
private:
    int m_intValue;
    std::string m_stringValue;

public:
    // constructor
    Foo();

    // constructor that takes int and string
    Foo(int intValue, const std::string& stringValue);

    // getters
    int getIntValue() const;
    std::string getStringValue() const;
    
    // setters
    void setIntValue(int intValue);
    void setStringValue(const std::string& stringValue);
};
}

#endif // FOO_H