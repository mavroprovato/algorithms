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
    * Binary Search Trees

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

Installation
============

The library is written against C11, so a conforming compliler is needed, like [gcc](https://gcc.gnu.org/) or [clang](https://clang.llvm.org/). Also, for the programs, an implemention conforming to POSIX.1-2008 is required. Currently the project has been tested with GCC version 4.8.2 on Ubuntu 16.04.

To build the library you can use the provided Makefile. `make` creates a debug build. `make release` creates a build without debug sumbols, and with compiler optimizations enabled.
