#include <iostream>
using namespace std;
#include <memory>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

int main()
{
    shared_ptr<Resource> ptr1{new Resource()};

    return 0;
}