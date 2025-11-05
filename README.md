# 🐚 Minishell

![42 Project](https://img.shields.io/badge/42%20Network-Minishell-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![Concepts](https://img.shields.io/badge/Concepts-Processes%20%26%20File%20Descriptors-yellowgreen?style=for-the-badge)

## 📚 Project Summary

**Minishell** is one of the most iconic projects in the 42 curriculum.  
Its goal is to build a simple shell — your own little **Bash** — capable of executing commands, handling pipes, redirections, environment variables, and basic built-in commands.

Through this project, I gained a deep understanding of **process management**, **file descriptors**, **signals**, and **command parsing** in C.

---

## 🧠 What I Learned in Minishell

This project strengthened my system programming and UNIX knowledge, especially around **process control**, **I/O redirection**, and **command parsing**.

### 🔹 Process and File Descriptor Management

* Creating and synchronizing child processes using `fork()` and `execve()`
* Managing input/output redirections with `dup()` and `dup2()`
* Building command pipelines using `pipe()`
* Understanding how file descriptors are duplicated and managed in UNIX

### 🔹 Parsing and Shell Logic

* Implementing a **lexer and parser** for shell syntax
* Handling **single** and **double quotes** properly during command parsing
* Expanding **environment variables** (e.g., `$USER`, `$PATH`, `$?`)
* Managing whitespace, tokens, and separators with precision

### 🔹 Signals and User Interaction

* Handling **Ctrl-C**, **Ctrl-D**, and **Ctrl-\** as Bash does
* Maintaining a smooth interactive prompt using **readline**
* Displaying command history and restoring the shell state gracefully

### 🔹 Robust and Modular C Design

* Designing clean, modular code following **Norminette** rules
* Avoiding memory leaks and ensuring proper cleanup
* Organizing the project into logical files and functions

---

## 📁 Project Structure

```bash
minishell/
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── executor.c
│   ├── builtins.c
│   ├── env.c
│   ├── signals.c
│   ├── utils.c
│   └── minishell.h
├── libft/
│   └── (libft source files)
├── Makefile
└── README.md
```

---

## ⚙️ Features Implemented

* Interactive shell with a working prompt and command history  
* Execution of commands via absolute or relative paths  
* Implementation of the following **built-ins**:
  - `echo` (with `-n` option)  
  - `cd`  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`  
* Support for:
  - Pipes (`|`)  
  - Redirections (`<`, `>`, `>>`, `<<`)  
  - Environment variable expansion (`$VAR`, `$?`)  
  - Quote handling (`'` and `"`)  

---

## 🧩 Technical Highlights

* **No global variables**, except for one signal indicator as per subject rules  
* Built on **POSIX system calls** for maximum portability  
* Memory safety ensured with proper free handling and leak testing  
* Precise error handling for invalid syntax and command failures  

---

## 🚀 Key Takeaways

Minishell taught me how a shell truly works under the hood — how commands are tokenized, parsed, and executed by the OS.  
It was an incredible experience to rebuild such a fundamental UNIX tool from scratch using pure C.

---

> _“Building Minishell was like creating a tiny universe where every process, pipe, and redirection had to play in harmony.”_
