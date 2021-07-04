# XORLinkedList

The project was implemented for the needs of *Algorithms and Data Structures* course.

The task was to implement a bidirectional list, where storage requirements are decreased due to bitwise XOR operation performed on addresses of previous and next nodes. It allows you to store only one address for every node, instead of two.


* **ACTUAL** - value of the currently pointed element. For an empty list it is NULL and after adding the first element to the list ACTUAL returns the value of that element as long as it is not moved by other operations.
* **NEXT** - prints the value of the ACTUAL successor setting it ACTUAL at the same time. If ACTUAL points to the last element of the queue, its successor will be the first element of the queue.
* **PREV** - prints the value of the predecessor ACTUAL setting it ACTUAL at the same time. If ACTUAL points to the first element of a queue, its predecessor will be the last element of the queue.
* **ADD_BEG** N - adding an element with value N to the beginning of the list.
* **ADD_END** N - adding an element with value N to the end of the list.
* **ADD_ACT** N - adding an element with the value of N as a predecessor of the currently selected element (ACTUAL).
* **DEL_BEG** - removes the first node from the list.
* **DEL_END** - removes the last node from the list.
* **DEL_VAL** N - removes from the list all nodes whose value is equal to N.
* **DEL_ACT** - removes from the list the node that ACTUAL points to, simultaneously setting ACTUAL to PREV. In the case that the PREV does not exist (ACTUAL was the first element of the list) ACTUAL shows the last element of the list.
* **PRINT_FORWARD** - prints the contents of the list from the first to the last element.
* **PRINT_BACKWARD** - prints the contents of the list from the last to the first element.
