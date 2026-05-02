# get_next_line test notes

Date: 2026-05-02

Source files were inspected only. No source code changes were made.

## Files checked

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

## Compile checks

Command shape used:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<value> -I. get_next_line.c get_next_line_utils.c <test_harness.c>
```

Results:

- `BUFFER_SIZE=1`: compiled.
- `BUFFER_SIZE=2`: compiled.
- `BUFFER_SIZE=5`: compiled.
- `BUFFER_SIZE=42`: compiled.
- `BUFFER_SIZE=10000`: compiled.
- `BUFFER_SIZE=1000000`: compiled and ran on a small file.
- `BUFFER_SIZE=10000000`: compiled, but crashed with segmentation fault on a small file.
- `BUFFER_SIZE=0`: failed to compile with `-Werror`.
- `BUFFER_SIZE=-1`: failed to compile.

Reason for `BUFFER_SIZE=0` / negative failures:

- `get_next_line_utils.c` declares `char tmp[BUFFER_SIZE] = {0};`.
- With `BUFFER_SIZE=0`, this becomes a zero-sized initialized array and GCC reports an error under `-Werror`.
- With `BUFFER_SIZE=-1`, the array size is negative.

Reason for very huge buffer crash:

- `get_next_line.c` has a stack array `char s[BUFFER_SIZE + 1];`.
- `get_next_line_utils.c` has a stack array `char tmp[BUFFER_SIZE];`.
- Very large `BUFFER_SIZE` values can overflow the stack.

## Functional tests

Tested cases:

- Normal file ending with newline: `abc\nxyz\n`
- Normal file not ending with newline: `abc\nxyz`
- Empty lines: `\n\nlast\n`
- Big line ending with newline: 100000 `A` characters + `\n`
- Big final line without newline: 100000 `B` characters and no final `\n`
- Same tests with `BUFFER_SIZE=1`, `2`, `5`, `42`, and `10000`

Single-file results:

- Lines ending with newline were returned including the newline.
- Final lines without newline were returned without a newline.
- Empty lines were returned correctly as `"\n"`.
- 100000-character lines worked with and without final newline.
- EOF after the last line returned `NULL`.

Performance note:

- Big lines with very small `BUFFER_SIZE`, especially `BUFFER_SIZE=1`, are slow because each chunk creates a new allocation and copies the full previous result again.

## Valgrind checks

Command shape used:

```sh
valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=99 <test_binary> ...
```

Checked:

- Big file with first big line ending in newline and second big line without final newline.
- File with empty lines.
- Interleaved two-file test.

Valgrind result:

- `0 bytes in 0 blocks` at exit.
- `All heap blocks were freed -- no leaks are possible`.
- `ERROR SUMMARY: 0 errors`.

Conclusion for normal successful reads:

- I did not reproduce a memory leak when the caller frees every returned line.

## Suspicious memory/correctness points

### 1. Missing `malloc` check

Location:

- `get_next_line_utils.c`, `ft_strjoin`

Problem:

- `result = malloc((ls + lr + 1) * sizeof(char));`
- The code immediately does `result[0] = '\0';`.
- If `malloc` returns `NULL`, this dereferences `NULL` and crashes.

### 2. Read error after partial allocation can leak

Location:

- `get_next_line.c`, after the read loop

Problem:

- If `result` already contains allocated data and a later `read()` returns `-1`, the function returns `NULL` without freeing `result`.
- This is hard to trigger with a normal regular file, but the path is present in the code.

### 3. Multiple file descriptors are not supported

Location:

- `get_next_line.c`, `static char rest[BUFFER_SIZE + 1];`

Problem:

- There is only one static `rest` buffer for all file descriptors.
- Interleaving reads from two files mixes leftover data between them.

Observed interleaved test examples:

- With `BUFFER_SIZE=5`, file A's second read started with data from file B.
- With `BUFFER_SIZE=42`, one file returned `NULL` too early and later calls returned lines from the other file.

This is a failure for bonus/multiple-FD behavior. It may be acceptable for the mandatory project if only one fd is tested at a time.

### 4. `BUFFER_SIZE=0` does not compile with strict flags

Location:

- `get_next_line_utils.c`, `char tmp[BUFFER_SIZE] = {0};`

Problem:

- Many testers compile with `-D BUFFER_SIZE=0`.
- This implementation should ideally compile and then return `NULL` because `get_next_line` checks `BUFFER_SIZE < 1`.
- Current code can fail before runtime because of the zero-sized array in the utility function.

### 5. Norminette issues

Norminette was installed and run.

Result:

- It reports missing/invalid 42 headers.
- It reports preprocessor spacing/indentation problems.
- It reports style issues in `get_next_line_utils.c` around `char tmp[BUFFER_SIZE]={0};`.
- It reports spacing/tab issues in the header prototypes and `handel_rest`.

## Overall conclusion

The implementation works for the main single-file happy paths I tested:

- file ends with newline
- file does not end with newline
- empty lines
- big lines
- small and medium positive `BUFFER_SIZE`

The main risks are:

- no `malloc` failure handling
- possible leak on `read()` error after partial line allocation
- no support for multiple file descriptors
- strict compile failure for `BUFFER_SIZE=0`
- stack overflow risk with extremely huge `BUFFER_SIZE`
- Norminette failures
