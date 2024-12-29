#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void create_file(const char *path);
void create_folder(const char *path);
void delete_file(const char *path);
void copy_file(const char *source, const char *destination);
void move_file(const char *source, const char *destination);
void display_file(const char *path);
void clear_terminal();

#endif
