#include <iostream>
#include <memory>

// ----------------------------------------------------------------------------
class MyClass
{
public:
    MyClass(int value) : m_value(value) {}
    void display() const { std::cout << "Value: " << m_value << std::endl; }

private:
    int m_value;
};

// ----------------------------------------------------------------------------
void displayValue(int value)
{
    // Create a unique_ptr to a MyClass object
    std::unique_ptr<MyClass> myClassPtr = std::make_unique<MyClass>(value);

    // Use the unique_ptr
    myClassPtr->display();

    // The unique_ptr myClassPtr will be automatically destroyed when this function exits,
    // and the dynamically allocated MyClass object will be deleted
}

// ----------------------------------------------------------------------------
int main()
{
    displayValue(10);

    // At this point, the MyClass instance has already been destroyed
    // because the unique_ptr went out of scope at the end of the displayValue function

    return 0;
}
