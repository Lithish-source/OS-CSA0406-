int main() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        printf("\nDirectory contents:\n");
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("opendir");
    }
    return 0;
}
