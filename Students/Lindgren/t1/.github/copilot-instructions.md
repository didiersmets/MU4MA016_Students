# Copilot Instructions for Lindgren/t1 C Codebase

## Overview
This workspace contains C source files for student assignments. The main file is `bubblesort.c`, which implements the bubble sort algorithm. The build output is `bubblesort.exe`.

## Architecture & Workflow
- **Single-file C programs**: Each assignment is typically a standalone C file. There is no cross-file dependency or shared library structure.
- **No external dependencies**: All code is standard C, compiled with GCC (MinGW-w64).
- **No custom frameworks or build systems**: Compilation is managed via VS Code tasks.

## Build & Run
- **Primary build tool**: GCC via MinGW-w64.
- **Recommended tasks**:
  - `C/C++: gcc.exe build active file`: Compiles the current file to an `.exe`.
  - `Build and Run C File (PowerShell)`: Compiles and runs the current file in one step. Uses PowerShell for Windows compatibility.
- **Example build command**:
  ```powershell
  C:\mingw64\bin\gcc.exe -fdiagnostics-color=always -g bubblesort.c -o bubblesort.exe; if ($?) { & .\bubblesort.exe }
  ```
- **Debugging**: Use VS Code's C/C++ extension and launch configurations for step-through debugging of `.exe` files.

## Conventions & Patterns
- **File naming**: Source files are named after the algorithm or assignment (e.g., `bubblesort.c`).
- **Output**: Executables are named to match the source file (e.g., `bubblesort.exe`).
- **No header files**: All logic is contained in a single `.c` file per assignment.
- **No test suite**: Manual testing via program output is expected.

## Key Files
- `bubblesort.c`: Main implementation example. Follow its structure for new assignments.
- `.vscode/tasks.json`: Contains build/run task definitions. Use or extend these for new files.

## Agent Guidance
- When adding new assignments, create a new `.c` file and update `.vscode/tasks.json` if custom build/run steps are needed.
- Maintain simple, readable C code. Avoid unnecessary complexity or external libraries.
- Use provided tasks for building and running code. Do not introduce makefiles or other build systems unless requested.
- Document any non-standard workflow changes in this file.

---
*Last updated: October 2, 2025. Please review and update if project structure changes.*
