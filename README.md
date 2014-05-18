ARC-Library
===========

The ARC library is a collection of code accumulated over the years, nothing more, nothing less.

> Don’t Live with Broken Windows

In order to avoid broken windows I have come up with a nomenclature which uniquely defines one or more characteristics of a certain algorithm or data structure, or a property of the function itself, when faced upon different levels of concurrency and paralelism.


Every module name or function conforms to the following pattern:

```
module_name_xy
```
Where `xy` is an optional suffix which can be one of the following:


| Suffix | Meaning                 | Description  |
| :---:  | ----------------------- | ------------ |
| `sr`   | <b>S</b>ignal <b>R</b>eentrant          |  |
| `tr`   | <b>T</b>hread <b>R</b>eentrant          |  |
| `ts`   | <b>T</b>hread & <b>S</b>ignal Reentrant | A function which is both thread-safe and reentrant. |
| `lf`   | Lock-free                         | A lock-free data structure implements thread-safety and reentrancy without the use of locks. |
| `mt`   | Multi-threaded                    | A function is said to be thread-safe if it can be called from more than one thread at the same time. |
| `i`    | Iterative                         |  |


A function is said to be reentrant if it can be interrupted and called again before the previous execution has ended.

A function is said to be thread-safe if it can be called from more than one thread at the same time.