The project comprises three `.c` files and two `.h` files, providing an organized structure that simplifies the implementation. The file **"lists.h"** contains all functions related to the train operations, while **"queue.c"** handles the queue system used for delaying command execution.

In the double-linked list with double sentinels, I named the wagon structure **"wagon"**, and each individual wagon is referred to as **"car"**. For the train, I used **"train"**, which includes a counter for the number of wagons and an iterator, named **"inspector"**, that moves between wagons, acting as a controller in the code.

The key functions in **"lists.c"** are as follows:
- **generate_car**: Allocates memory for a car, assigns a chosen symbol, and initializes the links to `NULL`, to be connected later when inserting a wagon.
- **init_train**: Although it could have been more elegant if it returned a `train *`, I chose to implement it this way to explore the use of double pointers. Memory is allocated for the structure, and the first car is initialized with `#`. The links between the car and the sentinel are established, the mechanic is set to point to the first car, and the train's length is set to 1.
- **move_left**: Moves the mechanic to the left; if it’s in the first car, it loops to the last one.
- **move_right**: If the mechanic is in the last car, a new one is created and added, otherwise, it simply moves to the next car.
- **write**: Changes the symbol of the car where the mechanic is located.
- **clear_cell**: Deletes the specified car.
- **clear_all**: The inspector iterates from the second car onwards, clearing everything after it. The first car remains, with its symbol reset to the initial state, as per the requirements.
- **show**: Iterates through the train, displaying all the car symbols. The car with the mechanic displays its symbol between `| |`.
- **show_current**: Displays only the car where the mechanic is positioned.
- **insert_left**: If the mechanic is in the first car, it shows an "ERROR"; otherwise, it inserts a new car using **generate_car**, updates the links, and increments the train's length.
- **insert_right**: Works similarly to **insert_left**.
- **search**: Allocates a dynamic string to copy each car's symbol starting from the mechanic's position. The train's length helps allocate the exact number of characters required. After iterating through the train and copying each car into the auxiliary string, it searches for the given substring. If a match is found, the pointer `p` points to the start; otherwise, it points to `NULL`. The mechanic is repositioned accordingly, and the dynamically allocated memory is freed.
- **search_left**: Works similarly to **search**, but iterates backwards using `prev` to find the position.
- **search_right**: Same as the other two, but iterates forward using `next`.
- **execute**: Receives a command string from a file and splits it using `strtok`. Based on the command, it parses the subsequent arguments to call the appropriate function.
In **"queue.c"**:
- **createnode**: Allocates memory for a new node with the command from the file.
- **add_queue**: Adds the new command to the queue using **createnode**.
- **printq**: Prints the elements of the queue.
- **pop_queue**: Returns the string from the first element of the queue and removes it.
- **freeq**: Frees the memory once the program finishes executing.
- **SWITCH**: Reverses the queue using an algorithm similar to one for a singly linked list. It uses three pointers to sequentially manage and reverse the links between nodes. Finally, the queue is reversed using the "cup method." While the length of the queue (len) wasn't used, it could be useful in future implementations.

In **"tema1.c"**:
Both input and output files are declared, and the number of commands is read from the keyboard. In the loop where commands are read, **SHOW**, **SHOW_CURRENT**, and **SWITCH** are handled separately using `strcmp`, as they produce immediate effects. Other commands are added to the queue, and when **EXECUTE** is called, the first command is dequeued and passed as an argument to its corresponding function. At the end, memory for both the train and the queue is freed, and the input/output files are closed.