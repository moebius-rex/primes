# Installing the Primes project

Throughout this guide, the `%` sign is used to indicate the command prompt; what follows the prompt is the command that you enter. All commands must be entered at a command prompt in a terminal window on `macOS` and `Linux` systems, or a `CMD` or `PowerShell` window on `Windows` systems. 

To download, build and run the implementations provided by this project, enter the following commands at a Linux, macOS or Windows command prompt:

```bash
% git clone https://github.com/moebius-rex/primes.git
% cd primes
% ./installer/install.sh
% make
```

If your system already has installed all dependencies required by this project, you will see console output that begins like this:

```
make --directory src/main
make --directory c/
make --directory sieve
gcc -c -o csieve.o csieve.c
ar: creating archive lib/libcsieve.a
rm csieve.o
/Library/Developer/CommandLineTools/usr/bin/make --directory app
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 .. 907 911 919 929 937 941 947 953 967 971 977 983 991 997
Found 168 integers(s) in 1000 integers in 4 microseconds
```

If however you see errors, it almost certainly means that you're missing at least one of the packages listed in the sections below and will need to install them using `apt`,  `brew`, `choco` or some other package manager depending on your operating system. Below are the instructions that will install these dependencies on three popular systems.

Once all required packages have been installed, complete the installation by running a script from the project directory:

```bash
% ./installer/install.sh
```

Follow any instructions the script may give you before trying to run the sieve implementations.

## Debian-based Linux

If you installed this project on a Debian, Ubuntu, Linux Mint or any other Debian-based Linux system, you can use **Advance Packaging Tool** package manager's `apt` command to download and install required packages. The package manager is pre-installed on Debian-based Linux systems.

First, update the local package list and then upgrade any existing packages:

```bash
% sudo apt update
% sudo apt -y upgrade
```

Install any of the packages required by this project:

```bash
% sudo apt install make
% sudo apt install maven
% sudo apt install gcc
% sudo apt install g++
% sudo apt install openjdk-11-jdk
% sudo apt install nodejs
% sudo apt install python3
```

## macOS

You can use the **Homebrew** package manager's `brew` command to download and install required packages.

To install Homebrew, enter the following commands at a command prompt:

```bash
% xcode-select --install
% curl -fsSL -o install.sh https://raw.githubusercontent.com/Homebrew/install/master/install.sh
```

Update the local package list and then upgrade any existing packages:

```bash
% brew update
```

Install any of the packages required by this project:

```bash
% brew install make
% brew install maven
% brew install gcc
% brew install g++
% brew install openjdk-11-jdk
% brew install python3
```

## Windows

> The commands described in this section correctly install the required packages for this project but a significant amount work remains to be completed to make the project work properly in a pure Windows environment. Any individual language implementation may be built or run successfully, but **Windows PowerShell** doesn't understand all of the commands used by `make` to *recursively* build, run and manage files in the project. If you still wish to install this project on a Windows system and use it in the manner for which it was designed, you should consider one of the following options:
>
> 1. Enable **Windows Subsystem for Linux** (WSL)  and install the project in WSL's Ubuntu virtual machine (VM).
> 2. Create a Linux VM using Oracle's **VirtualBox** product and install the project in the VM.
> 3. Create a Linux VM **Docker** image and install the project in the image.

You can use the **Chocolatey** package manager's `choco` command to download and install required packages. To install Chocolatey, follow the instructions [here](https://chocolatey.org/install).

To install any of the packages required by this project, open a **PowerShell** window *as Administrator* (e.g., type `powershell` in the Windows 10 search bar and click on the `Run as Administrator` option listed in the right hand panel of the popup menu that appears) and then enter any of the following commands as necessary:

```
% choco install make
% choco install maven
% choco install openjdk11
% choco install mingw
% choco install python3
```

The mingw package installs both `gcc` and `g++` compilers. If you needed to install a **Java JDK**, you will need to set the `JAVA_HOME` environment variable to point to the location where the package manager installed it, for example:

```powershell
% [Environment]::SetEnvironmentVariable("JAVA_HOME", "C:\Program Files\OpenJDK\openjdk-11.0.10_9")
% $env:JAVA_HOME C:\Program Files\OpenJDK\openjdk-11.0.10_9
```

## Docker

The project includes **Docker** configuration files that let you build images and launch containers that run the project's Sieve of Eratosthenes implementations. If you would like to use Docker **containers** to run the implementations, refer to [this guide](../docker/README.md) for instructions.

