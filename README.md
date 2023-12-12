# CPP
Interesting C++ features

## Templates
Templates in C++ are a powerful feature that allows for writing generic and reusable code.

### Function templates
Suppose we want to create a function that compares two variables and returns a reference to the larger one. We don't want to create such a function for each possible data type (e.g. ``int``, ``string``, etc.). This is where we can use _templates_.

In the following a _template function_ is defined that compares two values and returns the reference to the larger one.

```cpp
template <typename T>
T& getLarger(T& a, T& b)
{
    return (a > b) ? a : b;
}
```

This function can now be used for example to compare two variables as follows:

```cpp
// Example with integers
int int1 = 5, int2 = 10;
std::cout << "Larger int: " << getLarger(int1, int2) << std::endl;

// Example with strings
std::string string1 = "Hello", string2 = "World";
auto& largerString = getLarger(string1, string2);
```

Since the function returns a reference to the largest variable, this can be used to in the rest of the code for example as follows:

```cpp
largerString = "Hello World";
std::cout << "string2: " << string2 << std::endl;
```

The output of this code will be the value of ``string2`` which will be "Hello world!" because ``largerString`` is referencing ``string2``.

### Variadic templates
The ``...`` syntax creates a parameter pack or expands one. A _template parameter pack_ is a template parameter that accepts zero or more template arguments (non-types, types, or templates). A template with at least one parameter pack is called a variadic template.

For example, the following is an example of a template metaprogramming technique, specifically to calculate the arity (number of arguments) of a template parameter pack.

```cpp
template <typename... T>
struct arity {
  constexpr static int value = sizeof...(T);
};
```

Using this, the following code would print `Arity: 2` to the console.

```cpp
std::cout << "Arity: " << arity<int, float>::value << std::endl;
```

An interesting use for variadic templates is creating an initializer list from a parameter pack in order to iterate over variadic function arguments.

```cpp
#import <numeric>
template <typename First, typename... Args>
auto sum(const First firstArgument, const Args... otherArguments) -> decltype(firstArgument) 
{
  const auto values = {firstArgument, otherArguments...};
  return std::accumulate(values.begin(), values.end(), First{0});
}
```

Using this, the following statement would print "Sum: 55" to the console.

```cpp
std::cout << "Sum: " << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;

```

Note that adding `-> decltype(firstArgument)` to explicitly indicate the return type of the function is not strictly necessary when using C++14 or later, because in that case the compiler would deduce the return type based on what the function actually returns, assuming the return type is straightforward and can be inferred from the return statement.

## Range-based for loops

In most modern languages there is the possibility for iterating over the elements of a list. For example, in Python this would be done as follows:

```python
my_array = [1,2,3,4,5]
sum = 0
for x in my_array:
    sum += x
print(sum) # 15
```

In C++ the same functionality can be implemented as follows:

```cpp
std::array<int, 5> myArray {1, 2, 3, 4, 5};
int sum = 0;
for (int& x : myArray) sum += x;
std::cout << sum << std::endl; // 15
```

Note that the iterator `int& x` will be a reference to the elements in the array. This means that the following will square all the elements in the array. 

```cpp
for (int& x : myArray) x = x*x; // {1, 4, 9, 16, 25}
```

## Delegating constructors



```cpp
class SomeClass 
{
  public:
    int someInt;
    float someFloat;
  SomeClass(int someInt) : someInt{someInt}, someFloat{0} {}
  SomeClass() : SomeClass(0) {}
};
```



```cpp
SomeClass someClass;
std::cout << someClass.someInt; // 0  
```


## Direct initialization

Consider the following two statements:

```cpp
int a {1};
int b = 2;    
```

The two statements are examples of different initialization styles in C++: _direct initialization_ and _copy initialization_. Both are valid ways to initialize variables, but they have some differences in behavior, especially when dealing with complex types and classes. Let's look at each:

* __Direct Initialization__
``int a {1};``
This is an example of direct list initialization (introduced in C++11). It uses curly braces {}.
Direct list initialization is generally preferred for several reasons:
    * It prevents narrowing conversions (for example, initializing a float with an int value would be fine, but trying to initialize an int with a float value would cause a compile-time error).
    * It's consistent with the initialization of other types like objects of class types, arrays, and aggregates.
It can be used for direct initialization of objects of complex types.

* __Copy Initialization__
``int b = 2;``
This is an example of copy initialization. It uses the = symbol.
Copy initialization creates an object by initializing it with an existing object of the same type (or a type that can be converted to the desired type).

For simple fundamental types like ``int``, there's usually no practical difference in behavior or efficiency between copy initialization and direct initialization. However, for more complex types, especially classes with constructors, copy initialization may involve more overhead (like additional copy or move operations), although compilers are often able to optimize this away.

For complex types and in modern C++ code, direct initialization is often preferred for the reasons mentioned earlier, such as safety against narrowing conversions and consistency.

It's also a good practice to use direct list initialization in template code to ensure uniformity and avoid unexpected conversions.

In summary, while both styles are valid, direct list initialization is generally recommended in modern C++ programming, especially when working with complex types, to avoid potential issues and for consistency across different types of initializations.

## Selection statements with initializer

Consider the following code snippet:

```cpp
{
  std::lock_guard<std::mutex> lk(mx);
  if (v.empty()) v.push_back(val);
}
```

This can be also written as:

```cpp
if (std::lock_guard<std::mutex> lk(mx); v.empty()) 
{
  v.push_back(val);
}
```

This can be useful for several reasons:

* _Resource Management_
It ensures that the mutex is locked before the condition is checked and the subsequent block is executed, preventing race conditions in a multi-threaded environment. The mutex is unlocked when the ``if`` block is exited, which is taken care of by the ``std::lock_guard`` destructor.
<br>
* _Scope Control_
The scope of the lock (lk) is limited to the ``if`` block. This means that the mutex is only locked for the duration of the condition check and the execution of the ``if`` block, and not beyond it.
<br>
* _Readability and Maintenance_
This approach can make the code more readable and maintainable by keeping the lock acquisition and the condition check closely tied together and clearly indicating the scope in which the mutex is locked.

This pattern is commonly used in multi-threaded C++ code to ensure thread safety when accessing or modifying shared resources.

## Range-based for loop with initializer
This feature simplifies common code patterns, helps keep scopes tight, and offers an elegant solution to a common lifetime problem.

```cpp
for (auto v = std::vector{1, 2, 3}; auto& e : v)
{
  std::cout << e;
}
// prints "123"
```

## Classes and Structs

Classes and structs are similar with the exception that classes allow you to to encapsulate data and behavior, and control access through public interfaces. Structs can be used if we want a simple data structure with public access to its members.

In the following class definition, the members ``someInt`` and ``someFloat`` cannot be accessed from outside the class, while the ``sum()`` method can. 

```cpp
class SomeClass 
{
  int someInt;
  float someFloat;
    
  public:
    SomeClass(int someInt, float someFloat) : someInt{someInt}, 
                                              someFloat{someFloat} 
    {
      cout << "SomeClass(int, float) constructor called" << endl;
    }

    SomeClass() : SomeClass{0,0} 
    {
      cout << "SomeClass() constructor called" << endl;
    }

    decltype(auto) sum()
    {
      return someInt + someFloat;
    }

    ~SomeClass() { cout << "SomeClass destructor called" << endl; }
};
```

A struct with the same functionality can be defined as follows:

```cpp
struct SomeStruct 
{
  int someInt;
  float someFloat;

  decltype(auto) sum()
  {
    return someInt + someFloat;
  }

  SomeStruct(int someInt, float someFloat) : someInt{someInt}, 
                                             someFloat{someFloat} 
  {
    cout << "SomeStruct(int, float) constructor called" << endl;
  }

  SomeStruct() : SomeStruct{0,0} 
  {
    cout << "SomeStruct() constructor called" << endl;
  }

  ~SomeStruct() { cout << "SomeStruct destructor called" << endl; }
};
```

The only difference is that for this struct the attributes can be accessed.

Below are some of the statements in which the defined class and struct can be used.

```cpp
SomeClass someClass{1, 2.1};
cout << "Sum of someClass: " << someClass.sum() << endl;

SomeClass someEmptyClass;
cout << "Sum of someEmptyClass: " << someEmptyClass.sum() << endl;

SomeClass* pSomeClass = new SomeClass{1, 2.1};
cout << "Sum of pSomeClass: " << pSomeClass->sum() << endl;
delete pSomeClass;

SomeStruct someStruct{5, 0.0};
cout << "Sum of someStruct: " << someStruct.sum() << endl;

SomeStruct someEmptyStruct;
cout << "Sum of someEmptyStruct: " << someEmptyStruct.sum() << endl;

SomeStruct* pSomeStruct = new SomeStruct{5, 0.0};
cout << "Sum of pSomeStruct: " << pSomeStruct->sum() << endl;
```

## Initializer lists

A lightweight array-like container of elements created using a "braced list" syntax. For example, { 1, 2, 3 } creates a sequences of integers, that has type [``std::initializer_list<int>``](https://en.cppreference.com/w/cpp/utility/initializer_list) Useful as a replacement to passing a vector of objects to a function.

```cpp
int sum(const std::initializer_list<int>& list)
{
  int total = 0;
  for (auto& e : list)
  {
    total += e;
  }

  return total;
}

auto list = {1, 2, 3};
sum(list); // == 6
sum({1, 2, 3}); // == 6
sum({}); // == 0
```

