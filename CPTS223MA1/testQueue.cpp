#include "testQueue.hpp"

/*
Unit: queue::size ()
Description: test to determine if queue::size () returns correct
    queue size
Test steps:
1. Construct an empty queue object
2. Enqueue one item
3. Conditionally evaluate the valued returned by queue::size ()
Test data: size = 1
Precondition: queue object has one item
Postcondition: queue object still has one item
Expected result: queue::size () returns 1
Actual result: queue has size 2
Status: failed
*/
void testSize() {
    // create new queue
    queue q;
    // add to queue
    q.enqueue(1);

    // test that queue size is now 1
    if (q.size() == 1) {
        cout << "PASS: Queue with one item returns size 1" << endl;
    }
    else {
        cout << "FAIL: Queue with one item is not size 1" << endl;
    }
}

/*
Unit: queue::isEmpty ()
Description: test to determine if queue::isEmpty () returns 1 if a
    queue object is empty
Test steps:
1. Construct an empty queue object
2. Invoke queue::isEmpty ()
3. Conditionally evaluate the valued returned by queue::isEmpty ()
Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty
Expected result: queue is empty; 1 is returned
Actual result: queue is not empty; 0 is returned
Status: failed
*/
void testIsEmpty()
{
    // create new queue
    queue q;

    // test that queue returns as empty
    if (q.isEmpty()) {
        cout << "PASS: Empty queue recognized as empty" << endl;
    }
    else {
        cout << "FAIL: Empty queue not recognized as empty" << endl;
    }
}


/*
Unit: queue::isFull ()
Description: test to determine if queue::isFull () returns 1 if a
    queue object is full
Test steps:
1. Construct an empty queue object of capacity 1
2. Enqueue one item
3. Conditionally evaluate the valued returned by queue::isFull ()
Test data: size = 1
Precondition: queue object is full
Postcondition: queue object is still full
Expected result: queue is full; 1 is returned
Actual result: queue is full; 1 is returned
Status: passed
*/
void testIsFull() {
    // create new queue of capacity 1
    queue q = queue(1);
    // add item to queue, this should fill it
    q.enqueue(1);

    // test that queue returns as full
    if (q.isFull()) {
        cout << "PASS: Full queue recognized as full" << endl;
    }
    else {
        cout << "FAIL: Full queue not recognized as full" << endl;
    }
}

/*
Unit: queue::dequeue ()
Description: test to determine if queue::dequeue () makes list empty
    when last item is dequeued
Test steps:
1. Construct an empty queue object
2. Enqueue one item
3. Dequeue one item
4. Conditionally evaluate the valued returned by queue::isEmpty ()
Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty
Expected result: queue is empty; 1 is returned
Actual result: queue is not empty; 0 is returned
Status: failed
*/
void testDequeueEmpty() {
    // create new queue
    queue q;
    // add to queue
    q.enqueue(1);

    q.dequeue();

    // queue should now be empty
    if (q.isEmpty()) {
        cout << "PASS: Successfully added and removed from queue" << endl;
    }
    else {
        cout << "FAIL: Unable to remove item from queue" << endl;
    }
}

/*
Unit: queue::dequeue ()
Description: test to determine if queue::dequeue () removed correct
    item from queue when called
Test steps:
1. Construct an empty queue object
2. Enqueue two items (1,2)
3. Dequeue one item
4. Conditionally evaluate the remaining value in the list with queue::peek ()
Test data: size = 2
Precondition: queue object is empty
Postcondition: queue object has size 1
Expected result: queue:peek () returns 2
Actual result: queue:peek () returns 2
Status: passed
*/
void testDequeue() {
    // create new queue
    queue q;
    // add two items to queue
    q.enqueue(1);
    q.enqueue(2);

    q.dequeue();

    // remaining item in queue should be 2
    if (q.peek() == 2) {
        cout << "PASS: Successfully added two items to queue, dequeued one, and returned the remaining item" << endl;
    }
    else {
        cout << "FAIL: Remaining item in queue is unexpected" << endl;
    }
}

/*
Unit: queue::enqueue ()
Description: test to determine if queue::enqueue () does not add
    additional data to full queue object
Test steps:
1. Construct an empty queue object of capacity two
2. Enqueue three items (1,2,3)
3. Dequeue two items, list should be empty
4. Conditionally evaluate the whether list is empty
Test data: size = 2
Precondition: queue object is empty
Postcondition: queue object is still empty
Expected result: "Program Terminated" printed to screen; queue::isEmpty () returns 1
Actual result: "Program Terminated" printed to screen; queue::isEmpty () returns 0
Status: failed (but likely due to previous errors with queue::isEmpty ())
*/
void testEnqueueFull() {
    // create new queue of capacity 2
    queue q = queue(2);
    // add two items to queue (now filled)
    q.enqueue(1);
    q.enqueue(2);
    // adding third item to queue, but this should be discarded
    q.enqueue(3);

    // remove both items, queue should now be empty
    q.dequeue();
    q.dequeue();

    if (q.isEmpty()) {
        cout << "PASS: Attempted to add 3 items to queue of capacity 2, but rejected 3rd item" << endl;
    }
    else {
        cout << "FAIL: Attempted to add 3 items to queue of capacity 2, but unexpected result" << endl;
    }

}

/*
Unit: queue::enqueue ()
Description: test to determine if queue::enqueue () correctly adds
    item to queue
Test steps:
1. Construct an empty queue object
2. Enqueue one item (1)
3. Conditionally evaluate the whether correct item was queued using queue::peek ()
Test data: size = 1
Precondition: queue object is empty
Postcondition: queue object has size 1
Expected result: queue:peek () returns 1
Actual result: queue::peek () returns 1
Status: passed
*/
void testEnqueue() {
    // create new queue
    queue q;
    // add item to queue
    q.enqueue(1);

    if (q.peek() == 1) {
        cout << "PASS: Added 1 item to queue, and successfully peeked front of list" << endl;
    }
    else {
        cout << "FAIL: Added 1 item to queue, but unexpected peek" << endl;
    }
}

/*
Unit: queue::peek ()
Description: test to determine if queue::peek() returns the minimum integer value if the queue object is empty
Test steps:
1. Construct an empty queue object
2. Conditionally evaluate the value returned by queue:peek ()
Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty
Expected result: queue:peek () returns int minimum
Actual result: queue:peek () does not return int minimum
Status: failed
*/
void testPeekEmpty()
{
    // create new queue
    queue q;

    // test that empty peek returns int minimum
    if (q.peek() == numeric_limits<int>::min()) {
        cout << "PASS: Peek empty queue successfully returned int minimum" << endl;
    }
    else {
        cout << "FAIL: Peek empty queue did not return int minimum" << endl;
    }
}

/*
Unit: queue::peek ()
Description: test to determine if queue::peek () returns first
    item added to queue when two items are present
Test steps:
1. Construct an empty queue object of capacity two
2. Enqueue two items (1,2)
2. Conditionally evaluate the value returned by queue:peek ()
Test data: size = 2
Precondition: queue object is empty
Postcondition: queue object has size 2
Expected result: queue:peek () returns 1
Actual result: queue:peek () does not return 1
Status: failed
*/
void testPeek() {
    // create new queue
    queue q;

    // add two items to queue
    q.enqueue(1);
    q.enqueue(2);

    // peek should still return item fron front of list
    if (q.peek() == 1) {
        cout << "PASS: Added two items to queue, and peek returned first added value" << endl;
    }
    else {
        cout << "FAIL: Added two items to queue, and peek did not return first added value" << endl;
    }
}