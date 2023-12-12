# Vectors

## emplace_back

The function ``emplace_back()`` is a member function of the C++ Standard Library containers like std::vector, std::list, etc. It's used to construct an element in-place at the end of the container.

The primary advantage of ``emplace_back()`` over ``push_back()`` is that it avoids the extra copy or move operation, constructing the element directly in the storage location allocated by the container.

As an example, consider the following class.

```cpp
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
```

A vector can now be constructed comprising elements of this class:

```cpp
std::vector<MyClass> myVector;
```

The ``emplace_back()`` function can now be used to construct ``MyClass`` objects directly inside the vector:

```cpp
myVector.emplace_back(1, "Apple");
myVector.emplace_back(2, "Banana");
myVector.emplace_back(3, "Cherry");
```

For each ``emplace_back()`` call, the ``MyClass`` constructor is called with the corresponding arguments, demonstrating how objects are constructed in-place.
This in-place construction can lead to performance improvements, especially for large objects or in cases where copying or moving objects is expensive.

