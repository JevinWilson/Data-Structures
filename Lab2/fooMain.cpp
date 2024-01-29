#include "foo.h"

int main() {
    // Test default constructor
    testing::Foo foo;
    std::cout << "Original Foo: " << foo << std::endl;

    // Test constructor
    testing::Foo fooAppend(7, "Bob");
    std::cout << "Foo: " << fooAppend << std::endl;

    // Test setters
    foo.setIntValue(24);
    foo.setStringValue("Test setter");
    std::cout << "Changed Foo: " << foo << std::endl;

    // Test getters
    std::cout << "Test getter: " << foo.getIntValue() << std::endl;
    std::cout << "New: " << foo.getStringValue() << std::endl;

    return 0;
}
