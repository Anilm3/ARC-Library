ARC-Library
===========

The ARC library is a collection of code accumulated over the years, nothing more, nothing less.

Every module name or function conforms to the following pattern:

```
module_name_xy
```
Where `xy` is an optional suffix which can be one or more of the following:


| Suffix | Meaning       | Description  |
| :---:  | ------------- | ------------ |
| `r`    | Reentrant     | A function is said to be reentrant if it can be interrupted and called again before the previous execution has ended. |
| `t`    | Thread-safe   | A function is said to be thread-safe if it can be called from more than one thread at the same time. |
| `lf`   | Lock-free     | A lock-free data structure implements thread-safety and reentrancy without the use of locks. |

