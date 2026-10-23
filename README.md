# C String Library & s21_sprintf (School 21)

A custom implementation of the standard C `<string.h>` library and the `sprintf` function from `<stdio.h>`. This project was developed as a team project as part of the School 21 (42) curriculum.

The main goal is to deeply understand memory management, pointer arithmetic, variadic functions (`va_list`), and string parsing in C.

## 👨‍💻 My Contribution (Team Project)

This was a collaborative project. My primary responsibilities and contributions included:

1.  **Memory & String Functions (`jalfreza` module):** Fully implemented and tested `s21_memchr`, `s21_memcmp`, `s21_memcpy`, `s21_memset`, and `s21_strncat`.
2.  **`s21_sprintf` Formatting Parsers:** Developed the core parsing logic (`s21_parse_flags`, `s21_parse_width`, `s21_parse_precision`, `s21_parse_length`). This involved reading the format string, extracting flags (like `-`, `+`, ` `), width, precision, and length modifiers (like `h` and `l`) into a structured format.
3.  **`s21_sprintf` Base Specifiers:** Implemented the core output logic for base specifiers, including `%d`, `%c`, `%u`, `%s`, and the base `%f` (integer and fractional parts). The application of width and precision modifiers to these specifiers was handled by other team members.

## 🛠 Features (Full Library)

The library is compiled as a static archive (`s21_string.a`) and includes:

*   **Memory functions:** `memchr`, `memcmp`, `memcpy`, `memset`.
*   **String functions:** `strlen`, `strchr`, `strrchr`, `strstr`, `strpbrk`, `strncpy`, `strncat`, `strncmp`, `strcspn`, `strerror`, `strtok`.
*   **Formatting (`s21_sprintf`):**
    *   Specifiers: `%c`, `%d`, `%u`, `%f`, `%s`, `%%`.
    *   Flags: `-` (minus), `+` (plus), ` ` (space).
    *   Width, Precision, and Length modifiers.

## 📂 Project Structure

```text
.
|-- src/
|   |-- chatayav/       # String functions (strlen, strtok, etc.)
|   |-- dottedlu/       # String functions (strchr, strncmp, strerror, etc.)
|   |-- jalfreza/       # My contribution: memchr, memcmp, memcpy, memset, strncat
|   |-- sprintf/        # s21_sprintf implementation (parsers & base specifiers by me)
|   |-- Tests/          # Unit tests using the Check framework
|   |-- s21_common.h    # Common macros (S21_NULL)
|   `-- s21_string.h    # Main header file
|-- .clang-format       # Code style configuration
|-- Makefile            # Build instructions
`-- README.md
```

## 🚀 Build and Run

The project uses a `Makefile` for easy compilation. It requires the `Check` library for running unit tests.

### 1. Build the Static Library
To compile the source files and create the `s21_string.a` static library:
```bash
make
```

### 2. Run Tests
The project uses the [Check](https://libcheck.github.io/check/) framework for unit testing. To compile and run the tests:
```bash
make test
```

### 3. Generate Coverage Report
The project supports `gcov` for code coverage analysis. To generate an HTML report:
```bash
make gcov_report
```
*This will create a `gcov_report.html` file in the root directory.*

### 4. Clean up
To remove all object files, the static library, and coverage reports:
```bash
make clean
```

## 💻 Technical Highlights

*   **Variadic Functions:** Used `stdarg.h` (`va_list`, `va_arg`, `va_start`, `va_end`) to handle a variable number of arguments in `s21_sprintf`.
*   **Static Library:** Compiled object files into a `.a` archive using `ar rcs` for modular usage.
*   **Error Handling:** Implemented a cross-platform `s21_strerror` that returns correct error messages depending on the OS (handled `__APPLE__` vs Linux macros).
*   **Testing:** Achieved high coverage using the `Check` framework (assertion macros like `ck_assert_str_eq`, `ck_assert_int_eq`).
*   **Code Style:** Strict adherence to formatting rules via `.clang-format`.