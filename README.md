# 🐚 Minishell

**Minishell** is a Unix shell written in C as part of the 42 curriculum. The project reproduces the behavior of **bash**, including command execution, pipes, redirections, environment variable management, and signal handling.  
It teaches important concepts of **processes**, **system calls**, **memory management**, and **parsing**.

---

## 🧠 Project Overview

Minishell is designed to:

- Interpret and execute **commands** typed by the user.
- Handle **built-in commands** like `cd`, `echo`, `env`, `pwd`, `export`, `unset`, and `exit`.
- Manage **environment variables**.
- Support **input/output redirections** (`>`, `>>`, `<`).
- Support **pipelines** (`|`) between multiple commands.
- Handle **signals** (`Ctrl+C`, `Ctrl+\`) gracefully.
- Manage memory efficiently and avoid leaks.

The project emphasizes **robust parsing** and **process management** in Unix-like systems.

---

## ⚙️ Features

### Command Execution
- Supports executing external programs from the PATH.
- Uses `fork()`, `execve()`, and `waitpid()` to run commands in child processes.
- Handles **return codes** properly.

### Built-in Commands
- `echo`: prints arguments to stdout.
- `cd`: changes the current directory.
- `pwd`: prints the current working directory.
- `export`: sets environment variables.
- `unset`: removes environment variables.
- `env`: prints environment variables.
- `exit`: exits the shell with a status code.

### Environment Variables
- Supports `$VAR` expansion in commands.
- Maintains a local copy of environment variables.
- Handles changes in environment variables during the shell session.

### Redirections
- Output redirection: `>` (overwrite), `>>` (append).
- Input redirection: `<`.
- Handles multiple redirections in a single command.

### Pipelines
- Supports chaining multiple commands with `|`.
- Implements proper pipe creation and data flow between processes.

### Signal Handling
- `Ctrl+C` (SIGINT): interrupts the current command but does not exit the shell.
- `Ctrl+\` (SIGQUIT): ignored in the shell but handled properly in child processes.
- Ensures that signals don’t leave zombie processes.

### Parsing
- Tokenizes input correctly considering quotes (`'` and `"`) and escape sequences.
- Handles spaces, tabs, and special characters.
- Detects syntax errors like unexpected tokens or unmatched quotes.

### Memory Management
- Allocates memory dynamically for parsing and command structures.
- Frees all allocated memory at the end of execution or when errors occur.
- Avoids leaks and double frees.

---

## ⚙️ Compilation

To build the project, run:

```bash
make
```
This creates an executable named:
```bash
minishell
```
Other useful Makefile commands:
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything
```
## 🚀 Usage
Start the shell:
```bash
./minishell
```
Example commands:
```bash
$ echo Hello World
Hello World

$ pwd
/home/user

$ cd ..
$ pwd
/home

$ export MY_VAR=42
$ echo $MY_VAR
42

$ ls | grep minishell
minishell.c
```
Supports:
- Multiple pipes: ls | grep minishell | wc -l

- Input/output redirection: cat < input.txt > output.txt

- Quoted strings: echo "Hello $USER"

 ## 🧪 Error Handling

- Detects syntax errors:
  - Unexpected tokens
  - Missing arguments for redirections
  - Unmatched quotes
- Provides meaningful error messages to the user.
- Prevents the shell from crashing on invalid input.

## 🧵 Learning Outcomes

Through this project, I learned:

- How **Unix processes** work and how to manage them.
- How to handle **pipes and file descriptors** for inter-process communication.
- How to **parse complex input** with quotes, escapes, and environment variables.
- How to implement **built-in commands** and manage environment variables.
- How to handle **signals**.
- How to manage memory efficiently in a large C project.
