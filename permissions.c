#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "permissions.h"
#include "logger.h"
#include "utils.h"

void change_permissions(const char *path, const char *mode_str) {
    mode_t mode = 0;

    if (strlen(mode_str) != 9) {
        print_error("Invalid permissions format. Use 'rwxrwxrwx'.");
        return;
    }

    mode |= (mode_str[0] == 'r' ? S_IRUSR : 0);
    mode |= (mode_str[1] == 'w' ? S_IWUSR : 0);
    mode |= (mode_str[2] == 'x' ? S_IXUSR : 0);
    mode |= (mode_str[3] == 'r' ? S_IRGRP : 0);
    mode |= (mode_str[4] == 'w' ? S_IWGRP : 0);
    mode |= (mode_str[5] == 'x' ? S_IXGRP : 0);
    mode |= (mode_str[6] == 'r' ? S_IROTH : 0);
    mode |= (mode_str[7] == 'w' ? S_IWOTH : 0);
    mode |= (mode_str[8] == 'x' ? S_IXOTH : 0);

    if (chmod(path, mode) == -1) {
        perror("chmod failed");
        print_error("Failed to change file permissions.");
    } else {
        print_success("Permissions changed successfully.");
        log_operation("Change Permissions", path);
    }
}
