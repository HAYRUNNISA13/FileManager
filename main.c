#include <stdio.h>
#include <string.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"
#include "utils.h"

void list_operations()
{
    printf("\nAvailable Operations:\n");
    printf("  flist <path>           - List the contents of a directory\n");
    printf("  fcopy <src> <dest>     - Copy a file\n");
    printf("  fmove <src> <dest>     - Move a file\n");
    printf("  fremove <path>         - Delete a file or directory\n");
    printf("  fcreate <path>         - Create a new file\n");
    printf("  fmkdir <path>          - Create a new folder\n");
    printf("  fdisplay <path>        - Display the contents of a file\n");
    printf("  fchmod <path> <mode>   - Change permissions of a file or directory\n");
    printf("  fsearch <dir> <file>   - Search for a file in a directory\n");
    printf("  List of Operations     - Display all available commands\n");
    printf("  flog                   - Display all operated operations \n");
    printf("  clear                  - Clear the terminal\n");
    printf("  exit                   - Exit the program\n");
}

int main()
{
    char command[256];
    char path1[256], path2[256];

    printf("Welcome to the Terminal-Based File Manager!\n");
    printf("Type commands to perform operations.\n");
    printf("Type 'List of Operations' to see all available commands.\n");

    while (1)
    {
        printf("\nEnter command: ");
        fgets(command, 256, stdin);
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "List of Operations") == 0)
        {
            list_operations();
        }
        else if (strncmp(command, "flist", 5) == 0)
        {
            sscanf(command, "flist %s", path1);
            list_directory(path1);
        }
        else if (strncmp(command, "fcopy", 5) == 0)
        {
            sscanf(command, "fcopy %s %s", path1, path2);
            copy_file(path1, path2);
        }
        else if (strncmp(command, "fremove", 7) == 0)
        {
            sscanf(command, "fremove %s", path1);
            delete_file(path1);
        }
        else if (strncmp(command, "fmove", 5) == 0)
        {
            sscanf(command, "fmove %s %s", path1, path2);
            move_file(path1, path2);
        }
        else if (strncmp(command, "fcreate", 7) == 0)
        {
            sscanf(command, "fcreate %s", path1);
            create_file(path1);
        }
        else if (strncmp(command, "fmkdir", 6) == 0)
        {
            sscanf(command, "fmkdir %s", path1);
            create_folder(path1);
        }
        else if (strncmp(command, "fdisplay", 8) == 0)
        {
            sscanf(command, "fdisplay %s", path1);
            display_file(path1);
        }
        else if (strncmp(command, "fchmod", 6) == 0)
        {
            sscanf(command, "fchmod %s %s", path1, path2);
            change_permissions(path1, path2);
        }
        else if (strncmp(command, "fsearch", 7) == 0)
        {
            sscanf(command, "fsearch %s %s", path1, path2);
            search_file(path1, path2);
        }
        else if (strcmp(command, "flog") == 0)
        {
            FILE *logfile = fopen("operation_log.txt", "r");
            if (!logfile)
            {
                perror("Log file open failed");
                continue;
            }

            printf("\nOperation Log:\n");
            char line[256];
            while (fgets(line, sizeof(line), logfile))
            {
                printf("%s", line);
            }
            fclose(logfile);
        }
        else if (strcmp(command, "clear") == 0)
        {
            clear_terminal();
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Exiting the program...\n");
            break;
        }
        else
        {
            print_error("Unknown command. Type 'List of Operations' to see all available commands.");
        }
    }

    return 0;
}
