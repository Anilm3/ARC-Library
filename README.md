ARC-Library
===========

The ARC library is a collection of code accumulated over the years, nothing more, nothing less.

> Don’t Live with Broken Windows

In order to avoid broken windows I have come up with a nomenclature which uniquely defines one or more characteristics of a certain algorithm, function or data structure. Every module name conforms to the following pattern:

```
module_name_xy
```

And for the C++ library:

```
library::xy::module_name
```

Where `xy` is an optional suffix, describing the behaviour of the module under concurrent, parallel and interruptible environment. It can be one of the following:

| Suffix | Meaning                                 | Description  |
| :---:  | --------------------------------------- | ------------ |
| `ts`   | <b>T</b>hread-Safe      | A data structure which implements thread-safety by using conventional locks. |
| `lf`   | <b>L</b>ock-<b>F</b>ree | A data structure which implements thread-safety without the use of locks. |


Every independent function conforms to the following pattern:

```
function_name_ab
```

And every function belonging to a module conforms to this other pattern:

```
module_name_xy_function_name_ab
```

And for the C++ library:

```
module_name::function_name_ab
```

Where `ab` is an optional suffix which describes a characteristic of the underlying algorithm implemntation. It can be one of the following:

| Suffix | Meaning                                 | Description  |
| :---:  | --------------------------------------- | ------------ |
| `mt`   | <b>M</b>ulti-<b>T</b>hreaded            | An algorithm is said to be multi-threaded if it uses more than one thread to perform the desired computation. |
| `i`    | <b>I</b>terative                        | An algorithm is said to be iterative if it performs the desired computation through iterative constructs. |
| `r`    | <b>R</b>ecursive                        | An algorithm is said to be recursive if it performs the desired computation through direct or indirect calls to itself. |


Notes on thread-safety and reentrancy:

A function is said to be signal reentrant (async-signal safe or simply reentrant) if it can be interrupted and called again before the previous execution has ended. 
A function is said to be thread reentrant or thread-safe if it can be called from more than one thread at the same time.


