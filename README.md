# The Primes project

**Primes** is a project that implements the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) algorithm to find all prime numbers in a given range. The project implements the algorithm in several widely used programming languages and runs natively on supported platforms, or virtually via Docker containers.

## Goals

The primary goals of the project are to:

- demonstrate the similarities and differences between several popular programming languages by implementing the same easy-to-understand algorithm in each language
- provide basic implementations of all elements of a DevOps toolchain that supports the delivery, development, and management of software applications throughout the systems development life cycle

The project is young (just weeks old) and although it implements *most* of the DevOps toolchain, it does not currently include CI/CD (Jenkins/automated unit testing) or container orchestration (Kubernetes), but will in the future.

## Features

Each language-specific implementation of the Sieve of Eratosthenes algorithm comes in a minimum of two versions:
1. A *naïve* implementation that brute forces the solution. In other words, a hack — difficult to read and to maintain.
2. An *idiomatic* implementation that leverages features of the language to simplify development and maintenance. In this project, that typically means defining a separate, reusable `Sieve` component, for example, a class in Python, Java, C++, et al. In C, a procedural language with no intrinsic support for encapsulation, it means defining a `struct` that contains state, coupled with non-member functions that access or modify the state and implement the algorithm.

A third version is available for languages that provide a way to bind to C library functions. In these versions, a single O-O component encapsulates all interactions with the C library while the C library implements the sieve algorithm. Python's `ctypes` and Go's `cgo` packages are examples of simple but effective C library binding mechanisms.

Project features include:

- The sieve algorithm is implemented in six of the most widely used programming languages:
  - C
  - C++
  - Go
  - Java
  - JavaScript
  - Python
- One C++, one Go and one Python version are derived by binding to a C version exported as a shared lbrary. Java and server-side JavaScript (i.e., Node.js) versions may follow.
- The project uses **GNU Make** to:
  - compile and link C, C++ and Go implementations,
  - install reusable libraries, shared objects and header files,
  - run all, or a subset of, implementations,
  - remove generated files.
- The project uses **Maven** behind the scenes to compile and package Java implementations.
- All implementations are designed to be run from, and print to, a terminal window.
- Where possible, all implementations produce the identical output for the identical input.
- All C and C++ implementations produce zero `valgrind` errors or leaks when compiled with gcc/g++ on Debian-based Linux systems.
- The implementations have been tested on desktop Ubuntu and macOS installations as well as containerized Alpine, Fedora and Ubuntu installations.
- The project comes with **Docker** configurations that enable running algorithm implementations in containers.

## Environments

The project's Sieve of Eratosthenes implementations have been tested on Ubuntu 18.04 LTS, 20.04 LTS and Mac OS 11.2. Containerized versions of the implementations have been tested on Alpine Linux, Fedora and Ubuntu. The following language and tool versions were used:

| Language       | Tool      | Version   |
| :------------- | --------- | --------- |
| C              | `gcc`     | C11       |
| C++            | `g++`     | C++17     |
| Go             | `go`      | 1.16.3    |
| Java           | `javac`   | SE 11 LTS |
| JavaScript ES5 | `node`    | 14.16 LTS |
| Python         | `python3` | 3.8       |

## Installation

Follow [these instructions](./setup/INSTALL.md) to install the project.

## Running

Once you've completed the installation, you can run the implementations. To run them all back-to-back:

```bash
% prime
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in the range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 4 microseconds
[snip]
```

Alternatively, you can run only the implementations for a given language:

```bash
% ls src/main
Makefile  c/        cpp/      go/       java/     js/       python/
% prime java
Sieve of Eratosthenes: Find all prime numbers in a given range
[snip]
```

And finally, to run a given example of a given language:

```bash
% cd src/main/c
% ls
Makefile  app/      app2/     sieve/    sievex/
% make app2/
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in the range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 .. 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 11 microseconds
```

## Docker

The project includes **Docker** configuration files that let you build images and launch containers that run the project's Sieve of Eratosthenes implementations in docker containers. If you would like to use Docker **containers** to run the implementations, refer to [this guide](./docker/DOCKER.md) for instructions.

------

## Background

### Why choose the Sieve of Eratosthenes algorithm and not some other one?

Any popular algorithm could have been chosen as the basis for this project, as long as it satisfies the criteria set for the project:

- it's easy to understand
- it's of practical use
- it's implementable in just a few lines of code
- it takes as few inputs as possible
- its output is easily verifiable manually, at least for small input values

Several algorithms were considered, but the Sieve of Eratosthenes was selected because it absolutely satisfies each of the above criteria. Some of the other algorithms that were considered:

- The Euclidean algorithm for finding the greatest common divisor between two numbers, but it requires two inputs rather than one. Credit to Euclid though for proving in around 300 BCE that there are an infinite number of prime numbers.
- The Babylonian method for factorizing integers, but the algorithm requires a table of *prime numbers* as input.
- The Fibonacci Sequence. This algorithm is fascinating and has many practical uses, but output verification requires manually calculating binomial coefficients, which is difficult for all but the smallest of Fibonacci numbers.

### Algorithm pseudocode

The pseudocode used to implement this algorithm is included in this [Wikipedia article](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes), reproduced here for convenience:

```
algorithm Sieve of Eratosthenes is
    input: an integer n > 1.
    output: all prime numbers from 2 through n.

    let A be an array of Boolean values, indexed by integers 2 to n,
    initially all set to true.

    for i = 2, 3, 4, ..., not exceeding √n do
        if A[i] is true
            for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n do
                A[j] := false

    return all i such that A[i] is true.
```

### History of the Sieve of Eratosthenes

Much is known of [Eratosthenes](https://en.wikipedia.org/wiki/Eratosthenes), a polymath whose principal occupation was chief librarian at the [Library of Alexandria](https://en.wikipedia.org/wiki/Library_of_Alexandria), but little is known of the circumstances surrounding the derivation of his method for determining prime numbers. From [Wikipedia's](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) main entry on the topic:

> The earliest known reference to the sieve (Ancient Greek: κόσκινον Ἐρατοσθένους, *kóskinon Eratosthénous*) is in [Nicomachus of Gerasa](https://en.wikipedia.org/wiki/Nicomachus)'s *[Introduction to Arithmetic](https://en.wikipedia.org/wiki/Introduction_to_Arithmetic)*, an early 2nd cent. CE book, which describes it and attributes it to [Eratosthenes of Cyrene](https://en.wikipedia.org/wiki/Eratosthenes), a 3rd cent. BCE Greek mathematician.



------

## Notes

This section contains some notes about this installation.

### Maven errors

On Ubuntu systems, Maven commands issued by the project's top-level `Makefile` cause the error message `WARNING: An illegal reflective access operation has occurred` and others to be written to the console. The messages do not appear to affect behavior in any way and have been suppressed in Primes release 1.1.0.

### Java version

The project's Maven configuration file, `pom.xml`, specifies Java 11 as the version to use when building and running Java apps:

```
  <properties>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    <maven.compiler.source>11</maven.compiler.source>
    <maven.compiler.target>11</maven.compiler.target>
  </properties>
```

At the time of writing Java 11 is the default Java version on Linux distros that include it. You may of course change this to any version of Java you wish, but do remember to reflect your version of choice in `pom.xml`.

