ARC-Library
===========

The ARC library is a collection of code accumulated over the years, nothing more, nothing less.

Build System
----

Since creating this library is meant to be a fun time for me, as well as organizing all the code I had to be used in other projects, I decided to go for a non-recursive make build system.  I really enjoy working with Make directly as it gives you much more control over the build system and it forces you to fully understand and realize how the compilation of each component is being done and how the compiler and linker really work.

I worked a few days on it and reached a state where the system compiled but it didn't really feel right. I started investigating and reading a bit more in order to understand how I could improve my Makefiles so as to reduce the boilerplate code on each intermediate makefile and make the inclusion of dependencies, executables, libraries, etc, a bit more generic. After some work, I have to admit it was a lot of fun, but I realized that the non-recursive make approach was making me focus more on the build system than on the code.

So for now I've decided to do a fast switch to CMake, which requires just one file and it's incredibly easy to use but to be fair I've been using it for a while now at work so I'm pretty familiar with it. Using CMake has only advantages when compared to non-recursive make as it makes portability much easier and you don't even have to worry about dependency management, but then again is not as much fun and I'm quite certain non-recursive make is faster.



Naming Conventions
----

> Don’t Live with Broken Windows

In order to avoid broken windows I have come up with a nomenclature which uniquely defines one or more characteristics of a certain algorithm, function or data structure. Every module name conforms to the following pattern:

```
arc_module_name_xy
```

Where `xy` is an optional suffix, describing the behaviour of the module under concurrent, parallel and interruptible environment. It can be one of the following:

| Suffix | Meaning                                 | Description  |
| :---:  | --------------------------------------- | ------------ |
| `ts`   | <b>T</b>hread-<b>S</b>afe      | A data structure which implements thread-safety by using conventional locks. |
| `lf`   | <b>L</b>ock-<b>F</b>ree | A data structure which implements thread-safety without the use of locks. |


Every independent function conforms to the following pattern:

```
arc_function_name_ab
```

And every function belonging to a module conforms to this other pattern:

```
arc_module_name_xy_function_name_ab
```

Where `ab` is an optional suffix which describes a characteristic of the underlying algorithm implemntation. It can be one of the following:

| Suffix | Meaning                                 | Description  |
| :---:  | --------------------------------------- | ------------ |
| `mt`   | <b>M</b>ulti-<b>T</b>hreaded            | An algorithm is said to be multi-threaded if it uses more than one thread to perform the desired computation. |
| `i`    | <b>I</b>terative                        | An algorithm is said to be iterative if it performs the desired computation through iterative constructs. |
| `r`    | <b>R</b>ecursive                        | An algorithm is said to be recursive if it performs the desired computation through direct or indirect calls to itself. |


### Notes on thread-safety and reentrancy

* A function is said to be signal reentrant (async-signal safe or simply reentrant) if it can be interrupted and called again before the previous execution has ended. 
* A function is said to be thread reentrant or thread-safe if it can be called from more than one thread at the same time.


### TODO
* Add iterator insert before/after and erase to deque
* Improve dlist/deque/darray unit test to expand on iterator functionality