#include <iostream>
#include <numeric>

template <typename... T>
struct arity {
  constexpr static int value = sizeof...(T);
};

// Function template to return the larger of two values
template <typename T>
T& getLarger(T& a, T& b)
{
    return (a > b) ? a : b;
}

template <typename First, typename... Args>
auto sum(const First firstArgument, const Args... otherArguments) -> decltype(firstArgument) 
{
  const auto values = {firstArgument, otherArguments...};
  return std::accumulate(values.begin(), values.end(), First{0});
}

int main() 
{
    // Example with int
    int int1 = 5, int2 = 10;
    std::cout << "Larger int: " << getLarger(int1, int2) << std::endl;

    // Example with double
    double double1 = 3.5, double2 = 2.5;
    std::cout << "Larger double: " << getLarger(double1, double2) << std::endl;

    std::string string1 = "Hello", string2 = "World";
    auto& largerString = getLarger(string1, string2);
    largerString = "Hello World";
    std::cout << "string2: " << string2 << std::endl;


    std::cout << "Arity of int: " << arity<int, float>::value << std::endl;

    std::cout << "Sum: " << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;

    return 0;
}

