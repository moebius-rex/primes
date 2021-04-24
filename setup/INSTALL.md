# Installing the Primes project

> Throughout this guide, the `%` sign is used to indicate the shell command prompt; what follows the prompt is the command you need to enter. All commands must be entered in a terminal window on a `macOS`  or `Linux` system or virtual machine. 

## Summary

To download, setup and run the software provided by this project, enter the following commands at a **Linux** or **macOS** (native **Windows** is not supported) shell command prompt:

Installing the Primes project involves th f

```bash
% git clone https://github.com/moebius-rex/primes.git
% cd primes
% sudo ./setup/setup.sh
% make
```

If you do not intend to make contributions to the product and wish only to view its files, you can browse the files on [GitHub](https://github.com/moebius-rex/primes/), or download it as a [zip file](https://github.com/moebius-rex/primes/archive/refs/tags/v1.0.0.zip) instead; in either case, it isn't necessary to install the the **Git** version control system.

The following sections discuss these steps in more detail, starting with:

## Prerequisites

The project's software is designed to run on machines equipped with either **Linux** or **macOS**. Before downloading it, you should ensure that the systems on which you intend to run it have the required tools installed:

In addition to the baseline OS installation, the project requires developer tools which may or may not already be installed:

| Tool      | Description                        | Minimum version? |
| --------- | ---------------------------------- | ---------------- |
| `bash`    | Linux shell and command language   |                  |
| `gcc`     | GNU C compiler and linker          | C11              |
| `g++`     | GNU C++ compiler and linker        | C++17            |
| `git`     | Version control system             |                  |
| `make`    | Build automation tool              |                  |
| `maven`   | Java build automation tool         |                  |
| `node.js` | Server-side JavaScript interpreter |                  |
| `openjdk` | Java compiler and virtual machine  | JDK 11           |
| `python`  | Python script interpreter          | Python 3         |

[It's also very useful, but not essential, to have a [Markdown viewer/editor](https://typora.io/) installed.]

How these packages are installed varies by OS; the steps needed to install them on some popular operating systems are provided in the **Example project package downloads** section below.

## Download

Open a terminal window and navigate to the directory where you want to install the Primes project, then download it from **GitHub** (the `git` command output below is meant to be representative, not exact):

```bash
% git clone https://github.com/moebius-rex/primes.git
Cloning into 'primes'...
remote: Enumerating objects: 821, done.
remote: Counting objects: 100% (821/821), done.
remote: Compressing objects: 100% (336/336), done.
remote: Total 821 (delta 447), reused 798 (delta 436), pack-reused 0
Receiving objects: 100% (821/821), 166.29 KiB | 2.10 MiB/s, done.
Resolving deltas: 100% (447/447), done.
```

You'll see the project home directory contains the following files:

```bash
% ls primes
LICENSE              README.md            docker-compose.yaml  pom.xml
Makefile             docker/              setup/           src/
```

Here's a brief description of each file:

| Filename              | Content type       | Description                                                  |
| --------------------- | ------------------ | ------------------------------------------------------------ |
| `README.md`           | Markdown  Document | A document describing the project, [here](../README.md).     |
| `LICENSE`             | plain text         | The license describing your rights to use, distribute and modify the software contained in this project. |
| `Makefile`            | plain text         | A file used by the **make** command to orchestrate  compiling, running and managing  the project's implementations of the primes algorithm. |
| `docker-compose.yaml` | YAML               | A **Docker** configuration file that may be used to create Docker images that contain reduced-size versions of this project on several Linux platforms, and to launch containers that can run all of the algorithms. |
| `pom.xml`             | XML                | A **Maven** confuguration file that determines how to build the Jaca components of this project. |
| `setup/`          | directory          | Contains a shell script, **setup.sh**, that sets up a few key components of this project.  See the section below this one for more. |
| `docker/`             | directory          | Contains **Docker** configuration files that may be used to generate Docker images of this project on **Alpine**, **Fedora** and **Ubuntu** Linux systems. |
| `src/`                | directory          | The project source tree. It contains all implementations of the Sieve of Eratosthenes algorithm in different programming languages. |

The directory also contains three hidden files:

- `.git/`, the  Git repository for the project .
- `.gitignore`, a  file that tells Git which files and directories not to include in the repository.
- `.dockerignore`, a  file that tells Docker which files and directories not to include in a Docker image.

## Setup

The next step is to setup the project as follows:

```bash
% sudo setup/setup.sh
password: ••••••••
```

[`sudo` access is required because the setup script copies files to areas of the file system that are protected by superuser-level access.]

 Once you enter your password, setup proceeds silently until completion (in seconds).

Any problems encountered at this stage are almost certainly because one or more of the packages on which the product depends are not instailed locally. If you are having problems, go back to the **Prerequisites** section above to review. 

## Run

Now you are ready to run implementations of the primes algorithm. The project uses the **make** command for compiling, running and managing these implementations. To get started, go to the project home directory and enter the following command:

```bash
% make
    OR
% make all
```

The `make` command, with no arguments, or with only the `all` argument, runs all implementations of the algorithm. You should see output like this:

```bash
% make
make --no-print-directory --directory src/main
make --no-print-directory --directory c
make --no-print-directory --directory sieve
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 4 microseconds
[snip]
```

Return to the [main document](../README.md) to learn more about the project, or continue reading here to see how to install missing tools packages in different environments.

------

## Example project package downloads

This section describes how to install tools packages required by the project in a couple of common operating systems. But first:

### Installing Git

If you would like to make contributions to the Primes project, you will need to install Git, the version control software, to clone a copy of the project's repository on **Github** using the `git clone` command. You can learn how to install the `git` command [here](https://git-scm.com/download/linux).

### Debian-based Linux

If you are installing this project on a **Debian**, **Ubuntu**, **MX Linux**, **Linux Mint** or [other](https://www.tecmint.com/debian-based-linux-distributions/) **Debian-based Linux** system, you can use the Debian package manager's `apt` or `apt-get` commands to download and install packages that are not part of the standard distribution. The package manager is pre-installed on Debian-based Linux systems.

First, update the local package list and then upgrade any existing packages:

```bash
% sudo apt update
% sudo apt upgrade
```

If necessary, install the Git package:

```bash
% sudo apt install git
```

Install any of these packages required by this project:

```bash
% sudo apt install make
% sudo apt install maven
% sudo apt install gcc
% sudo apt install g++
% sudo apt install nodejs
% sudo apt install openjdk-11-jdk
% sudo apt install python3
```

### macOS

You can use the **Homebrew** package manager's `brew` command to download and install macOS packages.

To install Homebrew, enter the following commands at a command prompt:

```bash
% xcode-select --install
% curl -fsSL -o install.sh https://raw.githubusercontent.com/Homebrew/install/master/install.sh
% ./install.sh
```

This installs the `brew` command in `/usr/local/bin`, which you may want or need to add to your `PATH` environment variable. See [here](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-homebrew-on-macos) for a complete description of installing Homebrew on your Mac.

Before adding missing project tools, update the local Homebrew package list and upgrade any existing packages as follows:

```bash
% brew update
```

If necessary, install the Git package:

```bash
% brew install git
```

Install any of the packages required by this project:

```bash
% brew install make
% brew install maven
% brew install gcc
% brew install g++
% brew install node
% brew install openjdk-11-jdk
% brew install python3
```

### Notes for Windows users

The commands described in the **Windows** section below correctly install the required packages for this project. Any individual language implementation may be built or run successfully from **Windows PowerShell** but it doesn't understand all of the commands used by the **make** command to *recursively* build, run and manage files in the project. If you still wish to install this project on a Windows system and use it in the manner for which it was designed, you should consider one of the following options:

1. Enable **Windows Subsystem for Linux** (WSL)  and follow the instructions in this document to install the Primes project in WSL's **Ubuntu** virtual machine.
2. Build and run a Linux virtual machine using **[VMware Player](https://www.vmware.com/products/workstation-player.html)** or **[Oracle VirtualBox](https://www.virtualbox.org/)** and install the project in the virtual machine.
3. Build and run a Linux virtual machine using [**Docker**](https://www.docker.com/products/docker-desktop) with the project pre-installed in the virtual machine. This is probably the easiest and fastest way to setup the Primes project on Windows and the project even provides several [docker file examples](../docker/DOCKER.md) you can use to get started.

### Windows

You can use the **Chocolatey** package manager's `choco` command to download and install packages required by this project. To install Chocolatey, follow the instructions [here](https://chocolatey.org/install).

To install a package, open a **Windows PowerShell** window *as Administrator* (e.g., type `powershell` in the Windows 10 search bar and click on the `Run as Administrator` option listed in the right hand panel of the popup menu that appears) and then enter one of the following commands:

```
% choco install git
% choco install make
% choco install maven
% choco install openjdk11
% choco install mingw
% choco install python3
```

[The `mingw` package installs both `gcc` and `g++` compilers.]

If you needed to install a **Java JDK**, you will need to set the `JAVA_HOME` environment variable to point to the location where the package manager installed it, for example:

```powershell
% [Environment]::SetEnvironmentVariable("JAVA_HOME", "C:\Program Files\OpenJDK\openjdk-11.0.10_9")
% $env:JAVA_HOME C:\Program Files\OpenJDK\openjdk-11.0.10_9
```

## Docker

The project includes several Docker files that let you build images containing reduced-size versions of the project. Refer to [this guide](../docker/DOCKER.md) for instructions.

