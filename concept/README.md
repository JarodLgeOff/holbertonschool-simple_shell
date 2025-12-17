Simple Shell
Simple Shell is a simple UNIX command language interpreter that reads commands from either standard input or from a file. It is a Holberton School project designed to implement a basic shell similar to the sh (Bourne Shell) interface.

Table of Contents
*(#description) *(#requirements) *(#file-structure)

Installation

*(#built-in-commands)



Description
The Simple Shell is a command-line interpreter developed in C. It operates by creating a child process for each command entered by the user. The shell manages the environment variables, handles the PATH variable to locate executables, and supports basic error handling. It is designed to be memory-efficient and robust, handling end-of-file (EOF) conditions and signals like SIGINT (Ctrl+C) gracefully.

Key features include:

Displaying a prompt and waiting for user input.

Executing commands found in the system PATH or via absolute paths.

Handling command-line arguments.

Managing the process environment.

Implementing built-in commands like exit and env.

Requirements
Operating System: Ubuntu 14.04 LTS or 20.04 LTS.

Compiler: GCC 4.8.4 or later.

Compilation Flags: -Wall -Werror -Wextra -pedantic -std=gnu89

Style: Code must follow the Betty style guide.

Memory: No memory leaks (checked with Valgrind).

File Structure
The project is modularized to comply with the limit of 5 functions per file.

Installation
To install and compile the shell, follow these steps:

Clone the repository:

Navigate to the directory:

Compile the program:

Usage
The shell works in two modes: Interactive and Non-Interactive.

Interactive Mode
Run the executable. The shell will display a prompt (e.g., $ or #cisfun$ ) and wait for a command.

Non-Interactive Mode
Pipe commands into the shell or run from a script. The prompt is not displayed.

Built-in Commands
The shell supports the following built-in commands:

Flowchart
```mermaid
---
config:
  theme: redux
  layout: fixed
---
flowchart TB
    A(["Start"]) --> n3["🔧 Initialization<br>Environment &amp; Signals<br>(SIGINT, SIGQUIT)"]
    n3 --> n4["🔄 Start of Infinite Loop"]
    n4 --> n5@{ label: "💬 Display prompt '$ '" }
    n5 --> n6["📖 Reading: getline()"]
    n6 --> n7["✅ Command received"] & n8["⛔ EOF (Ctrl+D)<br>→ Free &amp; Exit"]
    n7 --> n9["🔍 Parsing: strtok()"]
    n9 --> n10{"❓ Empty command?"}
    n10 -- Yes --> n12["Free memory"]
    n10 -- No --> n13{"🔎 Is it a Built-in?<br>(env, exit, cd, etc.)"}
    n13 -- Yes --> n14["✅ Execute Built-in"]
    n14 --> n14b["💾 Store exit status"]
    n14b --> n12
    n13 -- No --> n16{"Is it an absolute path?<br>(/bin/ls or ./ls)"}
    n16 -- No --> n17["🔍 Search in PATH"]
    n17 --> n19{"Found in PATH?"}
    n19 -- No --> n20["❌ Error: command not found<br>exit_status = 127"]
    n20 --> n12
    n19 -- Yes --> n21["Build full path"]
    n16 -- Yes --> n22{"🔐 File accessible?<br>(access/stat)"}
    n21 --> n22
    n22 -- No --> n23["❌ Permission denied<br>or file not found<br>exit_status = 126/127"]
    n23 --> n12
    n22 -- Yes --> n25["🔀 Fork: fork()"]
    n25 --> n26{"❓ PID returned?"}
    n26 -- "-1" --> n27["❌ Fork error<br>exit_status = 1"]
    n27 --> n12
    n26 -- 0 --> n29["👶 Child Process"]
    n29 --> n29b["Restore default signals<br>(SIGINT, SIGQUIT)"]
    n29b --> n29c["Execute: execve()"]
    n29c --> n29d["⚠️ execve failed<br>perror + exit(126/127)"]
    n26 -- >0 --> n28["👨 Parent Process"]
    n28 --> n28b["Wait: wait(&status)"]
    n28b --> n28c["📊 Extract exit status<br>WIFEXITED/WIFSIGNALED<br>WEXITSTATUS/WTERMSIG"]
    n28c --> n28d["💾 Store in g_last_exit_status"]
    n28d --> n12
    n12 --> n31["🔁 Return to Loop"]
    n31 --> n4
    n8 --> n32(["🛑 Free all memory & Exit"])

    n5@{ shape: rect}
    style n8 fill:#ffd93d
    style n14 fill:#a8e6cf
    style n29d fill:#ff6b6b
    style n28d fill:#a8e6cf
    style n32 fill:#95e1d3
```

Start: Initialize environment.

Loop: Enter infinite loop.

Prompt: Check isatty; if true, print prompt.

Read: Get input line using getline. If EOF, exit.

Parse: Split line into tokens.

Check: Is the command a built-in?

Yes: Execute built-in function.

No: Search PATH or check absolute path.

Fork: Create child process.

Child: execve the command.

Parent: wait for child to finish.

Repeat: Free memory and return to Prompt.

Authors
Contributor 1 -

Contributor 2 -
