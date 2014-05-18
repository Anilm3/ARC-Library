ARC-Library
===========

The ARC library is a collection of code accumulated over the years, nothing more, nothing less.

> Don’t Live with Broken Windows

In order to avoid broken windows I have come up with a nomenclature which uniquely defines one or more characteristics of a certain algorithm, function or data structure. Every module name conforms to the following pattern:

```
module_name_xy
```

Where `xy` is an optional suffix, describing the behaviour of the module under concurrent, parallel and interruptible environment. It can be one of the following:


| Suffix | Meaning                                 | Description  |
| :---:  | --------------------------------------- | ------------ |
| `sr`   | <b>S</b>ignal <b>R</b>eentrant          | A function is said to be signal reentrant (async-signal safe or simply reentrant) if it can be interrupted and called again before the previous execution has ended. |
| `tr`   | <b>T</b>hread <b>R</b>eentrant          | A function is said to be thread reentrant or thread-safe if it can be called from more than one thread at the same time. |
| `ts`   | <b>T</b>hread & <b>S</b>ignal Reentrant | A function which is both thread-safe and reentrant. |
| `lf`   | <b>L</b>ock-<b>F</b>ree                 | A lock-free data structure implements thread-safety and reentrancy without the use of locks. |


Every independent function conforms to the following pattern:

```
function_name_ab
```

And every function belonging to a module conforms to this other pattern:

```
module_name_xy_function_name_ab
```

Where `ab` is an optional suffix which describes a characteristic of the specific algorithm impelemntation. It can be one of the following:

| Suffix | Meaning                                 | Description  |
| :---:  | --------------------------------------- | ------------ |
| `mt`   | <b>M</b>ulti-<b>T</b>hreaded            | A function is said to be thread-safe if it can be called from more than one thread at the same time. |
| `i`    | <b>I</b>terative                        |  |
| `r`    | <b>R</b>ecursive                        |  |




