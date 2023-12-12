# Threads

The ``std::thread`` library provides a standard way to control threads, such as spawning and killing them. 

## Thread vector

To demonstrate the use of threads, we're going to construct an example where a vector is created with two threads that are spawned to print to ``std::cout`` and then the program waits for them to finish. To prevent the threads from accessing the console simultaneously, a mutex is created to have one thread wait for the other.

First the following includes are needed:

```cpp
#include <thread>
#include <vector>
#include <iostream>
#include <sstream>
#include <mutex>
```

The mutex and print logic are encapsulated in ``ThreadSafePrinter`` class, reducing the complexity of thread function signatures.

```cpp
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
```

To demonstrate the use of ``std::ostringstream``. Instead of directly printing to ``std::cout`` inside ``printMessage``, the string can be build using ``std::ostringstream``. This minimizes the time for which the mutex is locked, as the string formatting does not require protection from concurrent access.

Next, a function is defined that is used by a thread. In this simple function the only thing that is done is printing the message.

```cpp
void someThreadFunction(ThreadSafePrinter& printer)
{
    printer.printMessage("Hello from someThreadFunction()!");
}
```

Now the main function can be created.

```cpp
int main()
{
    // ...
}
```

The first step is to create an instance of the ``ThreadSafePrinter`` and a vector to hold the threads.

```cpp
ThreadSafePrinter printer;
std::vector<std::thread> threadsVector;
```

The first thread is created which for demonstration purposes uses a lambda function which uses a reference to the created ``printer``.

```cpp
threadsVector.emplace_back([&printer]()
{
    printer.printMessage("Hello from the lambda function!");
});
```

Note that in the code above, the ``emplace_back()`` is used which calls the constructor of the thread. This constructor takes the function that the thread will run and the parameters of that function. This is also used to create the second thread which uses the ``someThreadFunction`` which takes a reference to the ``printer``.

```cpp
threadsVector.emplace_back(someThreadFunction, std::ref(printer));
```

Note that in the code above, ``std::ref`` is used to pass a reference to ``printer``. The function ``std::ref`` is a utility function that generates an object that encapsulates a reference to the passed argument. This is necessary because, when working with threads, it's common to need to pass references to shared objects to different threads. However, by default, the arguments passed to the ``std::thread`` constructor are copied into the thread's internal storage. This would defeat the purpose as we would end up with separate ``ThreadSafePrinter`` objects in each thread.

As the final step, the [``std::thread::join()``](https://cplusplus.com/reference/thread/thread/join/) function is called for each thread, which blocks and returns when the thread execution has completed.

```cpp
for (auto& thread : threadsVector)
{
    thread.join();
}
```

