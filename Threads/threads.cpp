#include <thread>
#include <vector>
#include <iostream>
#include <sstream>
#include <mutex>

class ThreadSafePrinter
{
public:
    void printMessage(const std::string& message)
    {
        std::ostringstream oss;
        oss << "Message: \"" 
            << message 
            << "\" from thread: " 
            << std::this_thread::get_id() << std::endl;

        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << oss.str();
    }

private:
    std::mutex coutMutex;
};

void someThreadFunction(ThreadSafePrinter& printer)
{
    printer.printMessage("Hello from someThreadFunction()!");
}

int main()
{
    ThreadSafePrinter printer;
    std::vector<std::thread> threadsVector;

    threadsVector.emplace_back([&printer]()
    {
        printer.printMessage("Hello from the lambda function!");
    });

    threadsVector.emplace_back(someThreadFunction, std::ref(printer));

    for (auto& thread : threadsVector)
    {
        thread.join();
    }
}
