#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: ./filestat <file_path>\n");
        return 1;
    }

    struct stat buf;
    if (lstat(argv[1], &buf) == -1) {
        perror("lstat");
        return 1;
    }

    printf("File Path: %s\n", argv[1]);

    if (S_ISREG(buf.st_mode)) {
        printf("File Type: Regular File\n");
    } else if (S_ISDIR(buf.st_mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISLNK(buf.st_mode)) {
        printf("File Type: Symbolic Link\n");
    } else {
        printf("File Type: Other\n");
    }

    printf("Size: %ld bytes\n", buf.st_size);

    char time_str[100];
    struct tm* tm_info = localtime(&buf.st_mtime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Last Modified: %s\n", time_str);

    return 0;
}
