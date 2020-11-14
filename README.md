# get_next_line
```c
int get_next_line(int fd, char **line);
```
Reads one line from input (without '\n') per call.
On EOF zero is returned and line is empty.
On error negative value is returned and line is null.
Multiple file descriptors is supported. (get_next_line_bonus.h)
Usage:
```c
#include "get_next_line_bonus.h"

int main() {
    int   fd = STDIN_FILENO;
    char  *line;

    while (get_next_line(fd, &line) > 0) {
        /* do stuff with line. */
        free(line);
    }
    /* if line is null, then error occuried. */
    if (line) {
        /* do stuff with last line, that does not ends with '\n'. */
        free(line);
    }
}
```