# Minishell

Minishell is a lightweight, custom Unix shell written in C. Built as a collaborative systems programming project, it replicates the core process management, pipeline execution, and state tracking mechanics of bash.

This repository highlights my specific contributions to the project: the system execution logic, signal management, and input/output routing.

## Core Contributions
For this two-person project, I focused on building the backend infrastructure that manages processes, file descriptors, and system signals.

- **Process Execution Engine:** Wrote the routing and execution logic for both custom built-ins and external system binaries. I used `fork`, `execve`, and `waitpid` to manage child processes, prevent zombie processes, and accurately capture application exit codes.
- **Pipeline & Advanced I/O Redirection:** Managed the file descriptors required for complex pipe chains (`|`) and standard input/output redirects (`<`, `>`, `>>`) using `dup2`.
- **Here-Documents (`<<`):** Created isolated child processes to handle here-documents securely, including expanding environment variables within the input.
- **Signal Management:** Intercepted and handled asynchronous system signals (`SIGINT`, `SIGQUIT`) using `sigaction` and `signal`. This ensures the interactive prompt gracefully interrupts without closing the main shell program.
- **Dynamic Prompt & State:** Built the interactive command-line interface using GNU `readline` to show a dynamic prompt with the current user and working directory, while tracking the exit status of the last executed command (`$?`).
- **Build System:** Wrote a modular Makefile with strict compilation flags (`-Wall -Wextra -Werror`) to compile and link internal files with external dependencies.

## Team Workflow
This shell was built in a two-person team. While I built the execution and systems interaction layer, my teammate built the front-end Lexical Analysis and Parsing Engine. She wrote the custom data structures and tokenization logic needed to read raw user input, handle quotes, and build the command structures that my execution code eventually runs.

## Technical Concepts Mastered
- **Low-Level C Programming:** Pointers, memory allocation, and preventing memory leaks in a continuous interactive loop (REPL).
- **UNIX System Calls:** Process creation, inter-process communication (pipes), and system signal handling.
- **File Descriptor Management:** Safely routing input/output streams and managing file tables across parent and child processes.

## Compilation & Usage
To compile and run the shell on a Linux/Unix system:

```bash
# Clone the repository
git clone <your-repository-url-here>
cd minishell

# Compile the project
make

# Run the shell
./minishell
```
