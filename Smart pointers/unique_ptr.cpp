#include <iostream>
#include <memory>  // For std::unique_ptr

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

void useResource()
{
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();
    // Do something with resource
} // resource goes out of scope here, and its destructor is called, releasing the resource

int main()
{
    useResource();
    // At this point, the Resource has already been released
    return 0;
}
