# Using Docker to run Sieve of Erastosthenes implementations

The Prime project includes **Docker** configuration files that let you build Docker images and launch Docker containers that run the project's Sieve of Erastosthenes implementations to compute and print all prime numbers in a given range. This document is a guide to building one or more of these images and launching one or more of these containers. An understanding of Docker is *not* required — simply follow the step-by-step instructions in this document.

## Prerequisites

- [Docker Desktop](https://www.docker.com/products/docker-desktop) installed and running on your desktop.

Throughout this guide, the `%` sign is used to indicate the command prompt; what follows the prompt is the command that you enter. All commands must be entered at a command prompt in a terminal window on `macOS` and `Linux` systems, or a `CMD` or `PowerShell` window on `Windows` systems. All commands should be run fron the top level of the Prime project installation, i.e., whatever location on disk you chose to clone the project's contents to.

## Step 1: Build Docker images

Up to three Docker images may be built, each one based on a different Linux distribution:

- Alpine 3.13, a container-only Linux distribution.
- Fedora 3.3, the current version of Fedora.
- Ubuntu Focal, a version of Ubuntu 20.04 LTS optimized for containers.

To build all images, enter the following commands from the project's top-level directory:

```
% docker-compose build
```

It takes in the order of a minute to build each image. Use `docker images` to view details about the resulting images:

```
% docker images
REPOSITORY   TAG       IMAGE ID       CREATED              SIZE
sieve        ubuntu    18e8f59a6c31   5 seconds ago        608MB
sieve        fedora    0abdd04df7f4   About a minute ago   1.12GB
sieve        alpine    5d00d4db8dd7   4 minutes ago        645MB
```

If you wished to build a subset of these images, say, the Alpine and Ubuntu images but not the Fedora image, you would enter the following command instead:

```
% docker-compose build alpine fedora
```

## Step 2: Start Docker containers

A Docker container is a **virtual machine** that loads and runs a Docker image. To start Docker containers for all Prime project images:

```
% docker-compose up -d
```

To start a selected container, say, the Fedora container, you would enter the following command instead:

```
% docker-compose up -d fedora
```

Use `docker ps` to view running containers:

```
% docker ps
CONTAINER ID   IMAGE          COMMAND               CREATED          STATUS          PORTS     NAMES
314fba7533e6   sieve:ubuntu   "tail -f /dev/null"   17 seconds ago   Up 15 seconds             ubuntu
16e78a1ee98e   sieve:alpine   "tail -f /dev/null"   17 seconds ago   Up 15 seconds             alpine
6f5b92d53669   sieve:fedora   "tail -f /dev/null"   17 seconds ago   Up 15 seconds             fedora
```

The `COMMAND` column shows the shell command that was called in the container once it was started. The Linux `tail -f /dev/null` command is a trick that keeps a container running until you decide to stop it with `docker-compose down` command; if we had given it a command that returns immediately, the container would stop once the command was completed.

## Step 3: Run sieve implementations in a Docker container

The `docker-conpose` exec command passes a command to a containerA sieve implementation for a particular container, say, the Alpine container, can be run as follows:

```
% docker-compose exec alpine make
[snip]
Sieve of Erastosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1,000 integers in 98 microseconds
[snip]
```

If you would like to run only a subset of the implementations in a given container, or you would simply like to explore a container's environment, you can open up a Bourne or Bash shell as follows:

```bash
% docker-compose exec ubuntu sh
         -- OR --
% docker-compose exec ubuntu bash
root@314fba7533e6:/project# cd src/main/python
root@314fba7533e6:/project/src/main/python# ls
Makefile  app.py  app2.py  sieve.py
root@314fba7533e6:/project/src/main/python# make
python/app
Sieve of Erastosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1,000 inclusive:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1,000 integers in 98 microseconds

python/app2
Sieve of Erastosthenes: Find all prime numbers in a given range
Prime numbers in range 0-1,000 inclusive:
2 3 5 7 11 13 17 19 23 29 .. 937 941 947 953 967 971 977 983 991 997 
Found 168 prime(s) in 1,000 integers in 1,021 microseconds
root@314fba7533e6:/project# 
```

## Step 4. Stop all containers

As already mentioned, the sieve implementation containers are configured to run until a command is issued to stop them as follows:

```bash
% docker-compose down  
Stopping ubuntu ... done
Stopping alpine ... done
Stopping fedora ... done
Removing ubuntu ... done
Removing alpine ... done
Removing fedora ... done
```

## Step 5: Clean up

Docker images take up disk space. If you wish to reclaim that space, you can delete all sieve implementation Docker images like this:

```bash
% docker system prune -a
WARNING! This will remove:
  - all stopped containers
  - all networks not used by at least one container
  - all images without at least one container associated to them
  - all build cache

Are you sure you want to continue? [y/N] y
Deleted Images:
deleted: sha256:c4b986c02bb51ee0a12ec704223350d908620c960f7f5be4e818ba21e46c7284
deleted: sha256:60df02f061f652d44f3bbe9d4fe93b9b7aefd00966cb54ded7bad9eb9a340f68
deleted: sha256:e728234f4ed0c033a420a6429bca05e2de29bba53b999f5c1dc45024459a0723
deleted: sha256:17683f22293e9cf90e02bcc103ef011778e4217b100a121bf3f45da07ceabf09

Deleted build cache objects:
[snip]
Total reclaimed space: 2.714GB
```
