# Tower-of-Hanoi


This program was implemented using specific structures for generic lists, queues and stacks. Other structures were used to retain the specific moves to solve the Hanoi system, but also a representative structure for a certain system (of a certain color), which retains the color of its discs, the number of discs, the rods, represented as stacks and the order of moves to resolve represented in a queue.


	Several specific functions for stacks/queues have been used: Pop, Push, Overturn, Overlay, IntrQ, ExtrQ, ConcatQ, FreeQueue, FreeStack. Several operations can be performed during the program: 


	-> Add: This command adds a new disc to an existing system of a particular color by calling the AddDisk function which inserts a disk into the stack so that the elements of the stack remain in a descending order from the bottom to the top and also increase the number of disks with 1. If the system with the specified color does not already exist, the SystemAllocation function is called, which creates a new complet system; so the specified disk will be the first disk of the system.


	-> Show: This command displays rods configuration at that time. Prior to display, the stack will be overturnedto start displaying the stack with the base. None of the 3 stacks (A, B and C) suffer a change.


	-> Show_moves: After receiving this command, the program will make the move list, represented by a queue, if the list has not already been created or if all the moves have not been exhausted. Then there will be displayed as many operations as specified in input. Displaying the elements in the queue is done by extracting the first element, displaying it, and inserting it into an auxiliary queue. If the number of required moves is less than the number of items in the queue, the rest of the elements will be moved in the auxiliary queue without displaying them. At the end, the auxiliary tail will be concatenated to the initial queue to avoid losing it.


	-> Play: This command is followed by a number of moves. Thus, under the same conditions as the Show_moves command, the move list is created. Then the number of required moves (maximum -> the number of queue elements) is performed, as they appear in the list of moves by moving one disk at a time from one stack to another.
