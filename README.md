# Terminal-Based File Manager

## Overview
This project is a command-line application for managing files and directories, developed using the C programming language. It leverages Unix/Linux system calls to perform essential file and directory operations efficiently. The project adheres to modular programming principles, ensuring maintainability, scalability, and ease of debugging.

## Features
The file manager supports the following operations:

1. **List Directory**
   - Lists contents of a directory, displaying file type, size, and permissions.
   - **System Calls:** `opendir`, `readdir`, `stat`

2. **Create Directory**
   - Creates a new directory with custom permissions.
   - **System Call:** `mkdir`

3. **Delete Directory**
   - Deletes an empty directory.
   - **System Call:** `rmdir`

4. **Create File**
   - Creates a new file at a specified path.
   - **System Call:** `creat`

5. **Delete File**
   - Deletes a specified file.
   - **System Call:** `unlink`

6. **Copy File**
   - Copies a file from source to destination.
   - **System Calls:** `open`, `read`, `write`

7. **Move File**
   - Moves a file by renaming it or performing a copy-and-delete operation.
   - **System Call:** `rename`

8. **Display File Content**
   - Displays the content of a file in the terminal.
   - **System Calls:** `open`, `read`, `write`

9. **Change Permissions**
   - Updates file or directory permissions.
   - **System Call:** `chmod`

10. **Search File**
    - Searches for files matching a name pattern within a directory.
    - **System Calls:** `opendir`, `readdir`, `strstr`

## Error Handling
- Provides meaningful error messages for all operations.
- Common errors include invalid paths, permission issues, and attempting to delete non-empty directories.
- Centralized error and success messages are implemented via helper functions in `utils.c`.

## Logging
- All operations are logged in a file (`file_manager.log`) with details such as operation type, timestamp, and result.

## Project Structure
The project follows a modular structure:
- **main.c:** Handles user input and dispatches commands.
- **file_operations.c:** Implements file-related operations (create, delete, copy, move, display).
- **directory_ops.c:** Implements directory-related operations (list, create, delete, search).
- **permissions.c:** Manages file and directory permissions.
- **logger.c:** Logs operations.
- **utils.c:** Provides utility functions for error and success messages.

## Contributors
- **Sinem Taşdemir**  
- **Hayrun Nisa Çelik**  
- **Betül Gül**  
- **Rayan Selo**  
