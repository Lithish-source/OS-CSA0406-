#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

extern int errno;

int main() {
    int fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);
    printf("fd = %d\n", fd);
    if (fd == -1) {
        printf("Error Number: %d\n", errno);
        perror("Program");
    } else {
        printf("File 'foo.txt' opened/created successfully.\n");
    }

    off_t offset = lseek(fd, 0, SEEK_END);
    printf("File size (using lseek): %ld bytes\n", offset);
    close(fd);

    struct stat st;
    if (stat("foo.txt", &st) == 0) {
        printf("File size (using stat): %ld bytes\n", st.st_size);
    } else {
        perror("stat");
    }

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        printf("\nDirectory listing:\n");
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("opendir");
    }
    return 0;
}
