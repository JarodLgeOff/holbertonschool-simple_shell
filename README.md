# Simple Shell
Simple Shell is a simple UNIX command language interpreter that reads commands from either standard input or from a file. It is a Holberton School project designed to implement a basic shell similar to the sh (Bourne Shell) interface.


## Summary
- [Description](#description)
- [Built-in](#built-in-commands)
- [Features](#Features)
- [Process-Management](#process-management--logic)
- [Structure-project](#Structure-project)
- [Flowchart](#flowchart)
- [Installation](#installation)
- [Compilation](#compilation)
- [Documentation_Man_Page](#Documentation_man_page)
- [Technologies used](#technologies-used)
- [Authors](#authors)

---

## Description

The Simple Shell is a command-line interpreter developed in C. It operates by creating a child process for each command entered by the user. The shell manages the environment variables, handles the PATH variable to locate executables, and supports basic error handling. It is designed to be memory-efficient and robust, handling end-of-file (EOF) conditions and signals like SIGINT (Ctrl+C) gracefully.

Key features include:

Displaying a prompt and waiting for user input.

Executing commands found in the system PATH or via absolute paths.

Handling command-line arguments.

Managing the process environment.

Implementing built-in commands like exit and env.

Usage
The shell works in two modes: Interactive and Non-Interactive.

Interactive Mode
Run the executable. The shell will display a prompt (e.g., $ or #cisfun$ ) and wait for a command.
exemple: 
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
```

Non-Interactive Mode
Pipe commands into the shell or run from a script. The prompt is not displayed.
exemple:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
```

---

## Built-in-Commands

The shell supports the following built-in commands that are executed directly by the shell process:

| Command | Description |
| --- | --- |
| **exit** | Terminates the shell. You can also provide an exit status (e.g., `exit 98`). |
| **env** | Prints the current environment variables to the standard output. |

---

## Features
* Display a prompt and wait for user input.
* Handle command lines with arguments.
* Handle the PATH environment variable.
* Built-ins: `exit`, `env`.
* Handle `Ctrl+D` (EOF) and `Ctrl+C` (SIGINT).

---

## #process-management--logic

The shell operates by managing the lifecycle of processes to execute user commands without crashing or exiting unexpectedly.

### 1. The Main Loop
The shell runs in a continuous loop, performing the following steps:
* **Prompt**: Displays a prompt (if in interactive mode).
* **Read**: Captures user input using `getline()`.
* **Parse**: Tokenizes the input string into a command and its arguments using `strtok()`.
* **Execute**: Attempts to run the command.

### 2. Fork, Execve, and Wait
To execute a command, the shell creates a new process so that the main program doesn't terminate after a command finishes:
* **`fork()`**: Creates a child process. Both the parent and child continue from the same point.
* **`execve()`**: Called within the child process to replace the current process image with the program to be executed (e.g., `/bin/ls`).
* **`wait()`**: The parent process waits for the child to finish, capturing its exit status before displaying the prompt again.

### 3. Environment & PATH
If the user provides a command name (like `ls`) instead of a full path (like `/bin/ls`), the shell:
1.  Retrieves the `PATH` variable from the environment.
2.  Splits the `PATH` into directories.
3.  Appends the command to each directory and uses `stat()` or `access()` to check if the file exists and is executable.

---

## Structure-project

```
holbertonschool-simple_shell/
├── man_1_simple_shell
├── shell.h
├── main.c
├── parser.c
├── executor.c
├── builtins.c
└── README.md
```     

---


## Flowchart

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
---

## Installation

- Requirements: Operating System: Ubuntu 14.04 LTS or 20.04 LTS.
- Style: Code must follow the Betty style guide.
- Memory: No memory leaks (checked with Valgrind).
- File Structure: The project is modularized to comply with the limit of 5 functions per file.

- Clone this repository:
- Open your preferred Terminal.
- Navigate to the directory where you want to clone the repository.
- Run the following command:
  
```git clone https://github.com/JarodLgeOff/holbertonschool-simple_shell.git```
- Open the cloned repository.

---

## Compilation

Compiler: GCC 4.8.4 or later.

Compilation Flags: -Wall -Werror -Wextra -pedantic -std=gnu89

---

## Documentation_man_page

The complete man page can be found in the file:  

[man_1_simple_shell.man](man_1_simple_shell.man)

---

## Technologies Used

<div align="left">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" height="40" alt="c logo"  />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/github/github-original.svg" height="40" alt="github logo"  />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/linux/linux-original.svg" height="40" alt="linux logo"  />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/windows8/windows8-original.svg" height="40" alt="windows8 logo"  />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/vscode/vscode-original.svg" height="40" alt="vscode logo"  />
</div>

---

## Authors

- [**Jarode Lange**](https://github.com/JarodLgeOff)
- [**Loïc Cerqueira**](https://github.com/Loic2888)
