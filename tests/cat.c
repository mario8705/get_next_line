#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

static void display_file(const char *path)
{
    char *line;
    int fd;
    int n;

    if (!path)
        fd = STDIN_FILENO;
    else
        fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "cat: %s: %s\n", path, strerror(errno));
        return ;
    }
    while ((n = get_next_line(fd, &line)) == 1)
    {
        puts(line);
        free(line);
    }
    if (n == -1)
    {
        fprintf(stderr, "cat: %s: Unexpected error from get_next_line\n", path);
    }
    close(fd);
}

int main(int argc, char **argv)
{
    int i;

    if (argc > 1)
    {
        i = 1;
        while (i < argc)
        {
            display_file(argv[i]);
            i++;
        }
    }
    else
    {
        display_file(NULL);
    }
    return (0);
}