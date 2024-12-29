#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "file_operations.h"
#include "logger.h"
#include "utils.h"
#include <libgen.h>

void create_file(const char *path) {
    int fd = creat(path, 0666);
    if (fd == -1) {
        print_error("File creation failed.");
    } else {
        print_success("File created successfully.");
        log_operation("Create File", path);
        close(fd);
    }
}
void create_folder(const char *path) {
    if (mkdir(path, 0755) == -1) {
        print_error("Folder creation failed.");
    } else {
        print_success("Folder created successfully.");
        log_operation("Create Folder", path);
    }
}

void delete_file(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) == -1) {
        print_error("Path does not exist or cannot be accessed.");
        return;
    }

    if (S_ISREG(path_stat.st_mode)) {
        
        if (unlink(path) == -1) {
            print_error("File deletion failed.");
        } else {
            print_success("File deleted successfully.");
            log_operation("Delete File", path);
        }
    } else if (S_ISDIR(path_stat.st_mode)) {
        
        if (rmdir(path) == -1) {
            print_error("Folder deletion failed. Make sure it is empty.");
        } else {
            print_success("Folder deleted successfully.");
            log_operation("Delete Folder", path);
        }
    } else {
        print_error("Unsupported file type.");
    }
}


void copy_file(const char *source, const char *destination) {
    char buffer[1024];
    int src_fd = open(source, O_RDONLY);
    if (src_fd == -1) {
        print_error("File open failed for reading.");
        return;
    }

    int dest_fd = open(destination, O_WRONLY | O_CREAT, 0666);
    if (dest_fd == -1) {
        print_error("File open failed for writing.");
        close(src_fd);
        return;
    }

    ssize_t bytes_read;
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes_read);
    }

    print_success("File copied successfully.");
    log_operation("Copy File", source);
    close(src_fd);
    close(dest_fd);
}
void clear_terminal() {
    #ifdef _WIN32
        system("cls"); // Windows için terminal temizleme
    #else
        system("clear"); // Linux/macOS için terminal temizleme
    #endif
    print_success("Terminal cleared.");
    log_operation("Clear Terminal", "N/A");
}



void move_file(const char *source, const char *destination) {
    struct stat path_stat;
    
    if (stat(destination, &path_stat) == -1) {
        if (mkdir(destination, 0755) == -1) {
            print_error("Failed to create destination directory.");
            return;
        }
    } else if (!S_ISDIR(path_stat.st_mode)) {
        print_error("Destination is not a directory.");
        return;
    }

    
    char *base = basename(source);
    char destination_with_filename[1024];
    snprintf(destination_with_filename, sizeof(destination_with_filename), "%s/%s", destination, base);

    copy_file(source, destination_with_filename);

    if (unlink(source) == -1) {
        print_error("Failed to delete source file after move.");
    } else {
        print_success("Source file deleted after move.");
    }
}


void display_file(const char *path) {
    char buffer[1024];
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        print_error("File open failed.");
        return;
    }

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);
}
