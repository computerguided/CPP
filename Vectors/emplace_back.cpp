#include <iostream>
#include <vector>
#include <string>

class MyClass
{
public:
    MyClass(int x, std::string y) : m_x(x), m_y(y) 
    {
        std::cout << "Constructed MyClass(" << m_x << ", " << m_y << ")" << std::endl;
    }

private:
    int m_x;
    std::string m_y;
};

int main()
{
    std::vector<MyClass> myVector;

    // Using emplace_back to construct MyClass objects directly inside the vector
    myVector.emplace_back(1, "Apple");
    myVector.emplace_back(2, "Banana");
    myVector.emplace_back(3, "Cherry");

    // The vector now contains three MyClass objects constructed in-place
    return 0;
}
