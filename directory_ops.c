#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>  
#include <string.h>
#include "directory_ops.h"
#include "logger.h"
#include "utils.h"

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        print_error("Directory open failed.");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;

    printf("Name\t\tType\t\tSize\t\tPermissions\n");
    printf("---------------------------------------------------------\n");

    while ((entry = readdir(dir)) != NULL) {
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == -1) {
            continue;
        }

        
        char *type = S_ISDIR(file_stat.st_mode) ? "Directory" : "File";

       
        char permissions[10];
        snprintf(permissions, sizeof(permissions), "%c%c%c%c%c%c%c%c%c",
            (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
            (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
            (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
            (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
            (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
            (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
            (file_stat.st_mode & S_IROTH) ? 'r' : '-',
            (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
            (file_stat.st_mode & S_IXOTH) ? 'x' : '-');

        
        printf("%-15s %-15s %-10lld %s\n", entry->d_name, type, file_stat.st_size, permissions);
    }

    closedir(dir);
}

void create_directory(const char *path) {
    if (mkdir(path, 0755) == -1) {
        print_error("Directory creation failed.");
    } else {
        print_success("Directory created successfully.");
        log_operation("Create Directory", path);
    }
}
void search_file(const char *directory, const char *filename) {
    DIR *dir = opendir(directory);
    if (!dir) {
        print_error("Failed to open directory.");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, filename)) {
            printf("Found: %s/%s\n", directory, entry->d_name);
        }
    }
    closedir(dir);
    log_operation("Search File", filename);
}


void delete_directory(const char *path) {
    if (rmdir(path) == -1) {  
        print_error("Directory deletion failed.");
    } else {
        print_success("Directory deleted successfully.");
        log_operation("Delete Directory", path);
    }
}

void search_directory(const char *path, const char *filename) {
    DIR *dir = opendir(path);
    if (!dir) {
        print_error("Directory open failed.");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, filename)) {
            printf("Found: %s\n", entry->d_name);
        }
    }
    closedir(dir);
}
