---
Copyright 229021 Shay Gordon

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
---
# Primes — The Sieve of Eratosthenes Project

**Primes** is a project that implements the **Sieve of Eratosthenes** algorithm in several popular programming languages for educational purposes.

## Purpose

The purpose of this project is to demonstrate differences and similarities between several popular programming languages by implementing the same algorithm in each language, and to demonstrate the comparative ease or difficulty in implementing the algorithm in each language. The project is *not* intended to provide a bullet-proof and thoroughly documented implementation of the algorithm in the selected languages. The project does *not* provide written documentation explaining the differences between the various language implementations — though it may do in the future — or extolling the virtues of one language over another; the hope instead is that downloaders will find their own uses for the project and its contents, that the set of languages will grow and that more language features will be explored as — or *if* — the project's momentum grows.

## Features

Each language-specific implementation of the Sieve of Eratosthenes algorithm comes in two versions:
- A naïve version that brute forces a solution. In other words, a hack — difficult to read and consequently, difficult to maintain.
- One or more object-oriented versions that should be more maintainable and use the best practices of the language. In all languages except C, this means extracting a `Sieve` class as a separate component. In the C implementation, it means extracting a transparent structure containing algorithm data, and functions that use that data to implement the algorithm — basically, a rudimentary C++ with an *explicit* `this` pointer and data encapsulation, but no data hiding.

Project features include:

- The sieve algorithm is implemented in the top five most popular programming languages at the time of writing:
  - C
  - C++
  - Java
  - JavaScript
  - Python
- One C++ and one Python implentation are derived by wrapping a C implementation. Similar Java and server-side JavaScript (node.js) implementations will follow.
- The project uses **Maven** under the hood to build Java implementations and GNU **Makefile** to build C and C++ implementations and to run all implementations.
- All implementations are designed to be run from, and print to, a terminal window.
- Where possible, all implementations produce the identical output for the identical input.
- All C and C++ implementations produce zero `valgrind` errors or leaks when compiled with gcc/g++ on Debian-based Linux systems.
- The implementations have been tested on desktop Ubuntu and macOS installations as well as containerized Alpine, Fedora and Ubuntu installations.
- The project comes with **Docker** configurations that enable running algorithm implementations in containers.

## Environments

The project's Sieve of Eratosthenes implementations have been tested on Ubuntu 20.04 LTS and Mac OS 11.2. Containerized versions of the implementations have been tested on Alpine Linux, Fedora and Ubuntu Focal. The following language and tool versions were used:

| Language       | Tool     | Version   |
| :------------- | -------- | --------- |
| C              | gcc      | C11       |
| C++            | g++      | C++17     |
| Java           | javac    | SE 11 LTS |
| JavaScript ES5 | node.js  | 14.16 LTS |
| Python         | pyrthon3 | 3.8       |

## Installation

Follow [these instructions](./installer/README.md) to install the project.

## Running

Once you've completed the installation, you can run the implementations. To run them all back-to-back (make sure you are in the project home directory):

```
% make
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 4 microseconds
[snip]
```

Alternatively, you can run only the implemnatations for a given language:

```
% cd src/main
% ls
Makefile  c/        cpp/      java/     js/       python/
% make c/
Sieve of Eratosthenes: Find all prime numbers in a given range
[snip]
```

And finally, for a given example of a given language:

```
% cd c
% ls
Makefile  app/      app2/     app3/
% make app2/
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 .. 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 11 microseconds
```

## Docker

The project includes **Docker** configuration files that let you build images and launch containers that run the project's Sieve of Eratosthenes implementations in docker containers. If you would like to use Docker **containers** to run the implementations, refer to [this guide](./docker/README.md) for instructions.

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

Much is known of [Eratothenes](https://en.wikipedia.org/wiki/Eratosthenes), a polymath whose principal occupation was chief librarian at the [Library of Alexandria](https://en.wikipedia.org/wiki/Library_of_Alexandria), but little is known of the circumstances surrounding the derivation of his method for determining prime numbers. From [Wikipedia](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)'s main entry on the topic:

> The earliest known reference to the sieve (Ancient Greek: κόσκινον Ἐρατοσθένους, *kóskinon Eratosthénous*) is in [Nicomachus of Gerasa](https://en.wikipedia.org/wiki/Nicomachus)'s *[Introduction to Arithmetic](https://en.wikipedia.org/wiki/Introduction_to_Arithmetic)*, an early 2nd cent. CE book, which describes it and attributes it to [Eratosthenes of Cyrene](https://en.wikipedia.org/wiki/Eratosthenes), a 3rd cent. BCE Greek mathematician.



------

## Notes

This section contains some notes about this installation.

### Maven errors

On Ubuntu, the `mvn clean` command invoked by running `make clean` on the top-level Makefile has been seen to cause the following messages to be written to the console. The messages do not appear to affect behavior in any way and can be ignored:

``` 
WARNING: An illegal reflective access operation has occurred
WARNING: Illegal reflective access by com.google.inject.internal.cglib.core.$ReflectUtils$1 (file:/usr/share/maven/lib/guice.jar) to method java.lang.ClassLoader.defineClass(java.lang.String,byte[],int,int,java.security.ProtectionDomain)
WARNING: Please consider reporting this to the maintainers of com.google.inject.internal.cglib.core.$ReflectUtils$1
WARNING: Use --illegal-access=warn to enable warnings of further illegal reflective access operations
WARNING: All illegal access operations will be denied in a future release
```

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

