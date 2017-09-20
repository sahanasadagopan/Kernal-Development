# cmocka example for ECEN 5013

* [cmocka](https://cmocka.org/)

* cmocka [API](https://api.cmocka.org/index.html)

cmocka is included in this repository as a git subtree. See
3rd-party/README.md for details.

## Requirements

* cmake - available through most package managers.

## Build

* building cmocka:

    ```SHELL
    make cmocka
    ```

    This will go into the 3rd-party libraries directory and call cmake
    correctly to build cmocka.

* building and running tests:

    ```SHELL
    make test
    ```
    
* building main executable

    ```SHELL
    make all
    ```
    
* cleaing up local build artifacts:

    ```SHELL
    make clean
    ```
    
* removing all generated files, including 3rd-party builds

    ```SHELL
    make clobber
    ```
    
## Source

Included source files are:

* doublell.{h|c} - simple demo library solving double linked list equations.

* test_doublell.c - unit tests for doublell solver.

* main.c - simple demo driver using library.

 Function - add element at the begining 
Function - add element at the center of the linked list
 Function - add element at a location where the memory isnt allocated yet
 Function - remove element
Function - remove element from origin , middle and end 
Function - search elements in the linkedlist
Function - size of the double linked list
Function - destroying the linked list
