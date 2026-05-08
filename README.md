# 42 Ecole

This repository contains my progress and projects from the **42 Cursus**.

## What is 42 Ecole?

[42](https://42.fr/en/homepage/) is a global software engineering school that offers a unique educational model:
*   **No Teachers & No Classes:** Learning is entirely peer-to-peer and project-based.
*   **Gamified Curriculum:** Students progress by completing projects, earning experience points (XP), and leveling up.
*   **The Norm:** Strict coding standards (Norminette) must be followed for all C projects. It enforces rules like a maximum of 25 lines per function, no `for` loops, and strict variable declaration rules.

## Topics Covered

The core curriculum heavily focuses on low-level programming to build a strong foundation before moving on to higher-level concepts. Key areas include:
*   **C Programming:** Memory management (malloc/free), pointers, linked lists, and data structures.
*   **Algorithms:** Sorting algorithms, pathfinding, and optimization.
*   **Unix / System Programming:** Multi-threading, processes (forks), pipes, signal handling, and file I/O.
*   **Graphics:** Raycasting, wireframe rendering, and handling window events using the MiniLibX.
*   **System Administration:** Virtual machines, Docker, system setup, and network configuration.

## The Core Curriculum Projects

Here is an overview of the projects generally found in the 42 Core Curriculum:

### Level 0
*   **[Libft](./)** - Creating a custom C library consisting of standard libc functions and additional utility functions (linked lists, string manipulations).

### Level 1
*   **[ft_printf](./)** - A custom implementation of the standard C `printf` function, learning about variadic arguments.
*   **[get_next_line](./)** - A function that reads and returns a single line from a file descriptor, teaching static variables and buffer management.
*   **[Born2beroot](./)** - System administration project requiring the setup of a virtual machine, Debian/CentOS installation, LVM, and strict security rules.

### Level 2
*   **[push_swap](./)** - An algorithmic project to sort data on a stack using a limited set of instructions and aiming for the lowest possible number of operations.
*   **[pipex](./)** - Recreating the behavior of shell pipes (`|`) in C using `fork`, `pipe`, `dup2`, and `execve`.
*   **[FdF](./)** - Introduction to graphical programming using MiniLibX. (Wireframe 3D rendering).

### Level 3
*   **[Philosophers](./)** - A classic threading and synchronization problem (Dining Philosophers problem) using mutexes and threads.
*   **[minishell](./)** - Recreating a basic bash-like shell, handling prompts, parsing, environment variables, built-ins, pipes, and redirections.

### Level 4
*   **[cub3D](./)** - Advanced graphics. Creating a 3D game engine using raycasting (like Wolfenstein 3D).
*   **[NetPractice](./)** - Understanding TCP/IP addressing, subnetting, and basic routing.
*   **[CPP Modules 00-04](./)** - Introduction to Object-Oriented Programming in C++ (Classes, instances, inheritance, polymorphism).

### Level 5
*   **[Inception](./)** - Introduction to Docker. Setting up a complete infrastructure using docker-compose (Nginx, WordPress, MariaDB).
*   **[webserv](./)** - Network programming. Creating an HTTP server from scratch in C++ (handling GET/POST, CGI, multiplexing).
*   **[CPP Modules 05-09](./)** - Advanced C++ concepts, templates, exceptions, and the Standard Template Library (STL).
