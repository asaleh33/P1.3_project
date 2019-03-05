# P1.3_project:  Advanced Programming

## C++ part

For this part of the project, we were requested to implement a **template** binary search tree (BST) algorithm, which includes the following:

* A node structure that stores a **pair** of a  **key** and the associated **value**.
* Iterators for the tree (`iterator` and `const_iterator`) and the corresponding functions of  `begin()`, `end()`, `cbegin()`, and `cend()`.
* `Insert()`function, which is used to insert a new node of  **pair** data structure (key-value). The function is called recursively and starts its process from the `head` node.
* `TreeTraversal()`function that prints the tree in a traversal order.
* `TreeFind()` function, which looks for a given key within the tree data structure. Additionally,  there are four find functions are implemented in this algorithm: (a) `TreeFindLargest`used to find the largest value in the tree, (b) `TreeFindSmallest()` used to look for the smallest element in the tree dataset, (c) I`sFound()` function that does same job as the main find function (`TreeFind()`), (d) `TreeFind_iter()`that looks for the data using the class `const_iterator`. This function is not efficient in searching for an element, particularly, with big data size. Similar to "linked list", the function iterates overall the tree elements. 
* `TreeClear()`function, which clears the tree structure by resetting the `head` node to `nullptr`and then sets empty tree of 0 size.

Except for `TreeFind_iter`, the above member functions start their recursive process from the `head` node.

### Code performance

The code performance was tested with respect the `TreeFind()` function for *unbalanced* and *balanced* tree. The benchmarking data (tree size & function time) are collected for each process in a separate file. Measuring time is shown in the main program `main.cpp`and carried out using `std::chrono::high_resolution_clock::now()` from `<chrono>`library.  The performance of the code is also tested using `std::map`. The results of this benchmarking process is shown the Figs.

![](./.aux/binary.png)

















