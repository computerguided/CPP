#include <iostream>
#include <vector>
#include <utility> // for std::move

class MovableClass
{
public:
    MovableClass() { std::cout << "Constructor" << std::endl; }
    ~MovableClass() { std::cout << "Destructor" << std::endl; }

    // Move constructor
    MovableClass(MovableClass&& other)
    { 
        std::cout << "Move Constructor" << std::endl; 
    }

    // Move assignment operator
    MovableClass& operator=(MovableClass&& other)
    { 
        std::cout << "Move Assignment Operator" << std::endl; 
        return *this; 
    }
};

void move_constructor()
{
    MovableClass obj1; // Constructor is called
    MovableClass obj2 = std::move(obj1); // Move Constructor is called

    // obj1 should not be used after this point
}

void move_assignment() 
{
    MovableClass obj1; // Constructor is called
    MovableClass obj2; // Constructor is called for another object

    obj2 = std::move(obj1); // Move Assignment Operator is called

    // obj1 should not be used after this point
}

int main()
{
    move_constructor();
    move_assignment();
    return 0;
}
