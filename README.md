[![Build Status](https://travis-ci.org/mavroprovato/algorithms.svg?branch=master)](https://travis-ci.org/mavroprovato/algorithms)

Introduction
============

A library that implements various data structures and algorithms in C.

The data structures implemented are:

* [Disjoint-set](https://en.wikipedia.org/wiki/Disjoint-set_data_structure) data structure (Union-Find).
* [Linked list](https://en.wikipedia.org/wiki/Linked_list) data structure.
* [Doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) data structure.
* [Stack](https://en.wikipedia.org/wiki/Stack_\(abstract_data_type\)) implementations based on:
    * Resizing arrays
    * [Linked lists](https://en.wikipedia.org/wiki/Linked_list)
* [Queue](https://en.wikipedia.org/wiki/Queue_\(abstract_data_type\)) implementations based on:
    * Fixed size arrays
    * Resizing arrays
    * [Linked lists](https://en.wikipedia.org/wiki/Linked_list)
* [Set](https://en.wikipedia.org/wiki/Set_\(abstract_data_type\)) implementations based on:
    * [Binary Search Trees](https://en.wikipedia.org/wiki/Binary_search_tree)
    * [Tries](https://en.wikipedia.org/wiki/Trie)

The algorithms implemented are:

* Various sorting algorithms:
    * [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort)
    * [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort)
    * [Selection sort](https://en.wikipedia.org/wiki/Selection_sort)
    * [Shellsort](https://en.wikipedia.org/wiki/Shellsort)
    * [Merge sort](https://en.wikipedia.org/wiki/Merge_sort)
    * [Quicksort](https://en.wikipedia.org/wiki/Quicksort)

Also, some programs are included which use those data structures and solve some classic problems. These programs are:

* Testing an expression for balanced parentheses.
* Checking whether a grid [percolates](https://en.wikipedia.org/wiki/Percolation_theory) or not.
* Calculating the running median of a list of integers

Installation
============

The library is written against C11, so a conforming compiler is needed, like [gcc](https://gcc.gnu.org/) or
[clang](https://clang.llvm.org/). Also, for the programs, an implementation conforming to POSIX.1-2008 is required.
Currently the project has been tested with GCC version 7.3.0 on Ubuntu 18.04.

The project uses [CMake](https://cmake.org/) as the build system. In order to build it, run the following commands:

```$bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```

Bibliography
============
* [Algorithms, 4th Edition](http://algs4.cs.princeton.edu/home/)
* [Introduction to Algorithms, 3rd Edition](https://mitpress.mit.edu/books/introduction-algorithms)
* Δομές Δεδομένων, Ιωάννης Μανωλόπουλος
* [Libalv](http://adtinfo.org/libavl.html/)
