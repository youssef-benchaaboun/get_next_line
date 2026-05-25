*This project has been created as part of the 42 curriculum by yoben-ch.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor.

The goal of the project is to understand how low-level input works in C with `read()`, how to manage dynamic memory safely, and how to preserve data between function calls using static variables. Each call to `get_next_line(int fd)` returns the next available line from the given file descriptor, including the final newline character `\n` when it exists. When there is nothing left to read, or when an error occurs, the function returns `NULL`.

This repository contains the mandatory implementation and a bonus implementation:

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`
- `get_next_line_bonus.c`
- `get_next_line_utils_bonus.c`
- `get_next_line_bonus.h`

The bonus version can keep separate read states for multiple file descriptors at the same time.

## Instructions

### Compilation

Compile the mandatory files with:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Compile the bonus files with:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

`BUFFER_SIZE` controls how many bytes are read from the file descriptor at each call to `read()`. The project must also compile without explicitly defining `BUFFER_SIZE`, because the header provides a default value.

### Basic usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Example compilation with a test file:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
./a.out
```

### Recommended tests

Test the function with different values of `BUFFER_SIZE`, for example:

```sh
-D BUFFER_SIZE=1
-D BUFFER_SIZE=42
-D BUFFER_SIZE=9999
```

Useful cases to test:

- An empty file.
- A file with one line and no final newline.
- A file with several lines.
- Very long lines.
- Standard input.
- Invalid file descriptors.
- Bonus: reading from several file descriptors in alternating order.

## Algorithm Explanation and Justification

The implementation uses a static buffer to keep unread characters between calls to `get_next_line`. This is necessary because a single call to `read()` may read more bytes than the current line needs. The extra bytes must not be lost, because they belong to the next line.

The mandatory algorithm works as follows:

1. Validate the input conditions.
   - If `BUFFER_SIZE` is not valid, the function returns `NULL`.
   - `read(fd, NULL, 0)` is used to detect an invalid file descriptor or read error without consuming data.

2. Keep a static buffer.
   - The static buffer stores data that was already read but not yet returned.
   - Because it is static, it keeps its content between calls to `get_next_line`.

3. Build the returned line.
   - The function joins the useful part of the static buffer to the current line.
   - It stops when a newline is found or when there is no more data to read.

4. Shift the buffer.
   - After extracting the current line, the remaining characters after the newline are moved to the beginning of the static buffer.
   - This prepares the buffer for the next call.

5. Return the result.
   - If a line was built, it is returned to the caller.
   - If the end of the file is reached and no line remains, the function returns `NULL`.

This approach is appropriate for the project because it reads only as much as needed, does not use `lseek()`, does not rely on global variables, and preserves unread data safely between calls.

### Bonus algorithm

The bonus implementation uses a two-dimensional static buffer:

```c
static char buffer[OPEN_MAX][BUFFER_SIZE + 1];
```

Each file descriptor has its own buffer. This allows calls such as `get_next_line(fd1)`, then `get_next_line(fd2)`, then `get_next_line(fd1)` again without mixing the saved content of different file descriptors.

## Resources

### Classic references

- `man 2 read` — documentation for the `read()` system call.
- `man 3 malloc` — documentation for dynamic memory allocation.
- `man 3 free` — documentation for releasing heap memory.
- C static variables — useful for understanding how data can persist between function calls.
- File descriptors in Unix-like systems — useful for understanding how files, standard input, and other input sources are represented.

### AI usage

AI was used only to help prepare and organize this `README.md` file according to the subject requirements. It was used for:

- Summarizing the purpose of the project.
- Structuring the documentation sections.
- Explaining the existing algorithm in clear language.
- Writing compilation and testing instructions.

AI was not used here to generate, modify, or debug the C source code of the project.
