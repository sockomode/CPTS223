/*

  Poor Design Attributes:

1. "using namespace std;" at file scope in a header file is bad practice. It can cause naming conflicts with functions that are self-declared or exist in other libraries.

2. The destructor for the queue class doesn't actually free the memory used by arrays. Instead the delete keyword should've been used instead.

3. For the enqueue and dequeue functions especially, the comments aren't detailed enough and are sort of vague. More comments would be beneficial for debugging and reading.

4. Defining SIZE seems unneccessary almost, especially when it's only used once to define the default maximum size of queue. And could lead to naming conflicts with other functions.

5. Having the queue class, the functions ,and main all in a single file causes unneccessary clutter.

*/


#include "queue.hpp"
#include "testQueue.hpp"
#include "testQueue.cpp"


int main()
{
    testIsEmpty();
    testIsFull();
    testSize();
    testPeek();
    testDequeue();
    testEnqueue();

    return 0;

}


