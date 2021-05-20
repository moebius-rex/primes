# Using Docker to run the Prime project

The Primes project includes **Docker** configuration files that let you build Docker images containing a reduced-size version of the Primes projectthat can then be run in Docker containers. This document is a guide to building these images and launching one or more of these containers. An understanding of Docker is *not* required — simply follow the step-by-step instructions in this document.

## Prerequisites

- [Docker Desktop](https://www.docker.com/products/docker-desktop) installed and running on your desktop.

Throughout this guide, the `%` sign is used to indicate the command prompt; what follows the prompt is the command that you enter. All commands must be entered at a command prompt in a terminal window on `macOS` and `Linux` systems, or a `CMD` or `PowerShell` window on `Windows` systems. All commands should be run fron the top level of the Primes project installation, i.e., whatever location on disk you chose to clone the project's contents to.

## Step-by-step guide

### Summary of steps

The detailed steps below execute the following commands:

```bash
% docker compose build
% docker compose up -d
% docker compose exec alpine   make
% docker compose exec alpinec  make
% docker compose exec alpinego make
% docker compose exec fedora   make
% docker compose exec ubuntu   make
% docker compose down
% docker system prune -a
```

### Step 1: Build Docker images

The project's `docker` subdirectory provides Docker files to build up to five Docker images, each one based on a different combination of Linux distribution and project installation:

- Alpine 3.13
- Fedora 33
- Ubuntu 20.04 LTS

Each image contains a copy of the project, omitting the `.git` repository, all docker files and project documents. The project files are installed in the `/prime` directory of the Docker image. Two additional containers are Alpine-based but contain C-only, and C- and Go-only projects installations. This makes these containers significantly smaller than the others and more suit ble for installation on embedded systems.

To build all images, enter the following command from the project's home directory:

```bash
% docker compose build
```

It takes in the order of a minute to build each image. Use `docker images` to view details about the resulting images:

```bash
% docker images
REPOSITORY   TAG       IMAGE ID       CREATED              SIZE
sieve        alpine     4bd9a664d878   14 minutes ago      996MB
sieve        alpinec    7e8690301fd4   14 minutes ago      163MB
sieve        alpinego   d33cbba884a0   14 minutes ago      483MB
sieve        fedora     e55b25c53a90   14 minutes ago      1.91GB
sieve        ubuntu     3e68256eab57   14 minutes ago      1.07GB
```

If you wished to build a subset of these images, say, the Alpine images only, you would enter the following command instead:

```bash
% docker compose build alpine alpinec alpinego
```

### Step 2: Start Docker containers

A Docker container is a **virtual machine** that loads and runs a Docker image. To start Docker containers for all Primes project images and run them in the background, i.e., detached from the terminal:

```bash
% docker compose up -d
[+] Running 4/4
 ⠿ Network "primes_default"  Created                                                              3.8s
 ⠿ Container alpine          Started                                                              3.8s
 ⠿ Container fedora          Started                                                              4.2s
 ⠿ Container ubuntu          Started                                                              3.6s
```

To start a selected container, say, the Fedora container, you would enter the following command instead:

```bash
% docker compose up -d fedora
```

Use `docker ps` to view running containers:

```bash
% docker ps
CONTAINER ID   IMAGE          COMMAND               CREATED          STATUS          PORTS     NAMES
82301cebc7e9   4bd9a664d878   "tail -f /dev/null"   16 minutes ago   Up 16 minutes             alpine
54622d651efe   e55b25c53a90   "tail -f /dev/null"   16 minutes ago   Up 16 minutes             fedora
5f049fa47dce   7e8690301fd4   "tail -f /dev/null"   16 minutes ago   Up 15 minutes             alpinec
ea3f5d67af1f   3e68256eab57   "tail -f /dev/null"   16 minutes ago   Up 15 minutes             ubuntu
ff7491759615   d33cbba884a0   "tail -f /dev/null"   16 minutes ago   Up 16 minutes             alpinego
```

The `COMMAND` column shows the shell command that was called in the container once it was started. The Linux `tail -f /dev/null` command is a standard trick that keeps a container running until you decide to stop it with `docker compose down` command; if we were to give it a command that returned immediately, the container would stop as soon as the command completed. The `NAMES` column provides the container names to use in container-ralted Docker commands. 

### Step 3: Run sieve implementations in a Docker container

The `docker compose exec` command runs a command in a named container. For example, to run all sieve implementations in, say, the Alpine container, you would enter the following:

```bash
% docker compose exec alpine make
[snip]
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1,000 integers in 98 microseconds
[snip]
```

If you would like to run only a subset of the implementations in a given container, say `ubuntu`, or you would simply like to explore a container's environment, you can open up a `Bourne` or `Bash` shell as follows:

```bash
% docker compose exec ubuntu sh
              OR
% docker compose exec ubuntu bash
[root@0a0689fe1cf4:/prime/src/main/python]# cd src/main/python
[root@0a0689fe1cf4:/prime/src/main/python]# ls
Makefile   app.py     app2.py    app3.py    csieve.py  sieve.py
[root@0a0689fe1cf4:/prime/src/main/python]# make
python/app
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 100 microseconds

python/app2
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 .. 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 188 microseconds

python/app3
Sieve of Eratosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 .. 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1000 integers in 17 microseconds

[root@0a0689fe1cf4:/prime/src/main/python]# 
```

### Step 4. Stop all containers

As already mentioned, the containers are configured to run until a command is issued to stop them, like this:

```bash
% docker compose down  
[+] Running 4/4
[+] Running 6/6
 ⠿ Container alpinec       Removed                                                             10.3s
 ⠿ Container fedora        Removed                                                             10.3s
 ⠿ Container alpinego      Removed                                                             10.5s
 ⠿ Container ubuntu        Removed                                                             10.5s
 ⠿ Container alpine        Removed                                                             10.4s
 ⠿ Network primes_default  Removed                                                              2.8s
```

### Step 5: Clean up

Docker images take up disk space, about 2.5GB in the case of the project's three of-the-shelf images. If you wish to reclaim that space, you can delete all  Docker images like this:

```bash
% docker system prune -a
WARNING! This will remove:
  - all stopped containers
  - all networks not used by at least one container
  - all images without at least one container associated to them
  - all build cache

Are you sure you want to continue? [y/N] y
Deleted Images:
untagged: sieve:ubuntu
deleted: sha256:3e68256eab57554048382d457cea4afad34801790533d2697dd203bfc072bf20
untagged: sieve:alpine
deleted: sha256:4bd9a664d878ab28c5bef64bb1c64969e6124359497ab28a9f1779142574d164
deleted: sha256:3b521395e68b1c3dc4ab10962864276143c1fe1c185b44250e2eb26a87488e94
untagged: sieve:fedora
deleted: sha256:e55b25c53a9006b5d6257d53d3ef31ad310156ce253979bc40d5f2ffba288973
deleted: sha256:77c08722778aa4c93d95c9d040e1828b7079970a26876457102f2f019e8391e7
deleted: sha256:866f9715f8b51708d550773e009e614233dda575626dfd17d2809745c43bcb02
deleted: sha256:02c8cf9848ba78d0996157ea4dcb02fa405fc42886135d30cce4fbf9a9a3b072
untagged: sieve:alpinec
deleted: sha256:7e8690301fd498f296fbfd451772355735ee0b288470ea13eca09e1b05074913
deleted: sha256:313b104e643f13f15b7348b43573fc5abc16eb788ce1380cc5a94fe7a7b35675
untagged: sieve:alpinego
deleted: sha256:d33cbba884a0d68eb4ca1fd87c9ae81d431fc3bc0f58c05dc270119d93e7d545

Deleted build cache objects:
[snip]
Total reclaimed space: 2.272GB
```

### Using the `prime` shell script

The project comes with a small shell script in the project's home directory, `prime`, that simplifies building, launching and managing Docker containers. Here are a few example commands:

```bash
% prime build           # build all docker images
% prime up              # start all docker containers
% prime ubuntu          # [build and] run all impls in ubuntu container
% prime fedora bash     # open bash shell in fedora container
```

Docker commands can also be chained together, for example, the following command stops all docker containers, deletes and then rebuilds all docker images, restarts docker containers and opens Alpine's default [Almquist](https://en.wikipedia.org/wiki/Almquist_shell) shell in the alpine container:

```bash
% prime down prune build up alpine sh
/prime # 
```
#### Note
The actual shell that the `sh` command starts depends on which Linux distribution you're using:
- Alpine Linux starts `ash`, the [Almquist](https://en.wikipedia.org/wiki/Almquist_shell) shell
- Fedora Linux starts `bash`, the Bourne Again Shell
- Ubuntu Linux starts `sh`, the Bourne Shell (Ubuntu also includes `bash`)

#### Note
This project does not support Docker-in-Docker. When we're ready to implement CI, e.g., using Jenkins, we'll create sibling, not child, Docker containers, as outlined in [this blog post](https://jpetazzo.github.io/2015/09/03/do-not-use-docker-in-docker-for-ci/). Therefore, Docker is not installed in project Docker images, and all Docker-related files are excluded from Docker images by the project's `.dockerignore` file.
