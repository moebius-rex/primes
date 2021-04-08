# Primes project

**Primes** is a project that implements the **Sieve of Erastosthenes** algorithm in several popular programming languages.

## Purpose

The purpose of this project is to demonstrate differences and similarities between several popular programming languages by implementing the same algorithm in each language, and to demonstrate the comparative ease or difficulty in implementing the algorithm in each language. The project is *not* intended to provide a bullet-proof and thoroughly documented implementation of the algorithm in the selected languages. The project does *not* provide written documentation explaining the differences between the various language implementations; the hope instead is that these implementations are small enough to be easily digestible and allow for easy side-by-side comparisons.

## Features

- The sieve algorithm is implemented in several languages:
  - C
  - C++
  - Java
  - JavaScript
  - Python
- Each language implementation of the sieve algorithm comes in two versions:
  - A naïve version that brute forces the results. In other words, a bit of a hack.
  - A more refined version that uses features and best practices of the language to create a more maintainable implementation.
- Uses **Maven** under the hood to build Java implementations and GNU **Makefile** to build C and C++ implementations.
- Uses **Makefile** to run all implementations.
- All implementations are designed to be run from, and print to, a terminal window.
- Where possible, all implementations produce the identical output for the identical input.
- All C and C++ implementations produce zero `valgrind` errors or leaks when compiled with gcc/g++ on Debian-based Linux systems.
- The implementations have been tested on Ubuntu 20.04 LTS and Mac OS 11.2.
- The project comes with a docker file that builds an image that runs every implementation.

## Environments tested

The project's sieve implementations have been tested on Ubuntu 20.04 LTS and Mac OS 11.2. The following language and tool versions were used:

| Language       | Tool     | Version   |
| :------------- | -------- | --------- |
| C              | gcc      | 11        |
| C++            | g++      | 15        |
| Java           | javac    | 13        |
| JavaScript ES6 | node.js  | 14.16 LTS |
| Python         | pyrthon3 | 3.8       |



## Installation

To clone, build run the implementations provided by this project, enter the following commands at a Linux, macOS or Windows command prompt:

```
git clone https://github.com/moebius-rex/primes.git
cd primes
make
```

If your system already has installed all dependencies required by this project, you will see console output that begins like this:

```
make --no-print-directory -C src/main
make --no-print-directory -C c
make --no-print-directory -C app
bin/App 1000
Sieve of Erastosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 .. 907 911 919 929 937 941 947 953 967 971 977 983 991 997
Found 168 integers(s) in 1000 integers in 4 microseconds
```

If however you see errors, it almost certainly means that you're missing at least one of the following dependencies and will need to install additional packages:

You may need to add  using `apt`,  `brew`, `choco` or some other package manager depending on your system. Below are the instructions that will install these dependencies on a Debian-based Linux system: 

### Debian-based Linux

If you installed this project on a Debian, Ubuntu, Linux Mint or any other Debian-based Linux system, you can use **Advance Packaging Tool** package manager's `apt` command to download and install required packages. The package manager is pre-installed on Debian-based Linux systems.

First, update the local package list and then upgrade any existing packages:

```
sudo apt update
sudo apt -y upgrade
```

Install any of the packages required by this project:

```
sudo apt install make
sudo apt install maven
sudo apt install gcc
sudo apt install g++
sudo apt install openjdk-11-jdk
sudo apt install nodejs
sudo apt install python3
```

### macOS

You can use the **Homebrew** package manager's `brew` command to download and install required packages.

To install Homebrew, enter the following commands at a command prompt:

```
xcode-select --install
curl -fsSL -o install.sh https://raw.githubusercontent.com/Homebrew/install/master/install.sh
```

Update the local package list and then upgrade any existing packages:

```bash
brew update
```

Install any of the packages required by this project:

```
brew install make
brew install maven
brew install gcc
brew install g++
brew install openjdk-11-jdk
brew install python3
```

### Windows

> The commands described in this section correctly install the required packages for this project but work remains to be done to make the project work properly in a pure Windows environment. Any language implementation may be built or run successfully, but **Windows PowerShell** doesn't understand all of the commands used by `make` to recursively build, run and manage files in the project. If you still wish to install this project on a Windows system and use it in the manner for which it was intended, you should consider one of the following options:
>
> 1. Enable **Windows Subsystem for Linux** (WSL)  and install the project in WSL's Ubuntu VM.
> 2. Create a Linux VM using Oracle's **VirtualBox** product and install the project in the VM.
> 3. Create a Linux VM **Docker** image and install the project in the image.

------

You can use the **Chocolatey** package manager's `choco` command to download and install required packages. To install Chocolatey, follow the instructions [here](https://chocolatey.org/install).

To install any of the packages required by this project, open a **PowerShell** window *as Administrator* (e.g., type `powershell` in the Windows 10 search bar and click on the `Run as Administrator` option listed in the right hand panel of the popup menu that appears) and then enter any of the following commands as necessary:

```
choco install make
choco install maven
choco install openjdk11
choco install mingw
choco install python3
```

The mingw package installs both `gcc` and `g++` compilers. If you needed to install a **Java JDK**, you will need to set the `JAVA_HOME` environment variable to point to the location where the package manager installed it, for example:

```
[Environment]::SetEnvironmentVariable("JAVA_HOME", "C:\Program Files\OpenJDK\openjdk-11.0.10_9")
$env:JAVA_HOME C:\Program Files\OpenJDK\openjdk-11.0.10_9
```

## Background

### Why choose the Sieve of Erastosthenes algorithm and not some other one?

Any popular algorithm could have been chosen as the basis for this project, as long as it satisfies the criteria set for the project:

- it's easy to understand
- it's of practical use
- it's implementable in just a few lines of code
- it takes as few inputs as possible
- its output is easily verifiable manually, at least for small input values

Several algorithms were considered, but the Sieve of Erastosthenes was selected because it absolutely satisfies each of the above criteria. Some of the other algorithms that were considered:

- The Euclidean algorithm for finding the greatest common divisor between two numbers, but it requires two inputs rather than one. Credit to Euclid though for proving in around 300 BCE that there are an infinite number of prime numbers.
- The Babylonian method for factorizing integers, but the algorithm requires a table of prime numbers as input.
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

### History of the Sieve of Erastosthenes

Much is known of [Erastothenes](https://en.wikipedia.org/wiki/Eratosthenes), a polymath whose principal occupation was chief librarian at the [Library of Alexandria](https://en.wikipedia.org/wiki/Library_of_Alexandria), but little is known of the circumstances surrounding the derivation of his method for determining prime numbers. From [Wikipedia](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)'s main entry on the topic:

> The earliest known reference to the sieve (Ancient Greek: κόσκινον Ἐρατοσθένους, *kóskinon Eratosthénous*) is in [Nicomachus of Gerasa](https://en.wikipedia.org/wiki/Nicomachus)'s *[Introduction to Arithmetic](https://en.wikipedia.org/wiki/Introduction_to_Arithmetic)*, an early 2nd cent. CE book, which describes it and attributes it to [Eratosthenes of Cyrene](https://en.wikipedia.org/wiki/Eratosthenes), a 3rd cent. BCE Greek mathematician.

# Notes

This section contains some notes about this installation.

## Maven errors

On Ubuntu, the `mvn clean` command invoked by running `make clean` on the top-level Makefile has been seen to cause the following messages to be written to the console. The messages do not appear to affect behavior in any way and can be ignored:

``` 
WARNING: An illegal reflective access operation has occurred
WARNING: Illegal reflective access by com.google.inject.internal.cglib.core.$ReflectUtils$1 (file:/usr/share/maven/lib/guice.jar) to method java.lang.ClassLoader.defineClass(java.lang.String,byte[],int,int,java.security.ProtectionDomain)
WARNING: Please consider reporting this to the maintainers of com.google.inject.internal.cglib.core.$ReflectUtils$1
WARNING: Use --illegal-access=warn to enable warnings of further illegal reflective access operations
WARNING: All illegal access operations will be denied in a future release
```

## Java version

The project's Maven configuration file, `pom.xml`, specifies Java 11 as the version to use when building and running Java apps:

```
  <properties>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    <maven.compiler.source>11</maven.compiler.source>
    <maven.compiler.target>11</maven.compiler.target>
  </properties>
```

At the time of writing Java 11 is the default Java version on Linux distros that include it. You may of course change this to any version of Java you wish, but do remember to reflect your version of choice in `pom.xml`.
