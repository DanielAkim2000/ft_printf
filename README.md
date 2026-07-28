*This project has been created as part of the 42 curriculum by demane.*

# ft_printf

A reimplementation of the C standard library function `printf()`, developed as a 42 school project.

---

## Description

**ft_printf** aims to recreate the behavior of `printf()` from the C standard library. The main educational goal is to learn how to handle a **variable number of arguments** through variadic functions (`stdarg.h`), while designing clean, modular, and extensible code.

The library parses a format string, interprets conversion specifiers (and optional flags), retrieves the corresponding arguments, and writes the formatted output to the standard output. It returns the number of characters printed.

This project builds on a local copy of **libft**, reused for string, memory, and character utilities.

### Library overview (`libftprintf.a`)

The delivered artifact is a static library: **`libftprintf.a`**.

| Component | Role |
|-----------|------|
| `ft_printf` | Entry point: walks the format string, dispatches conversions, returns the print count |
| Format parser | Reads flags, width, precision, and conversion type into a `t_format` structure |
| Conversion handlers | One path per type (`c`, `s`, `p`, `d`/`i`, `u`, `x`/`X`, `%`) |
| Padding helpers | Apply width / precision and bonus flags (`-`, `+`, space, `0`, `#`) |
| **libft** | Supporting library (compiled from `./libft`) embedded into `libftprintf.a` |

Public prototype:

```c
int	ft_printf(const char *str, ...);
```

---

## Features

### Mandatory conversions

| Specifier | Description |
|-----------|-------------|
| `%c` | Character |
| `%s` | String (NULL prints `(null)`) |
| `%p` | Pointer address in hexadecimal |
| `%d` / `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` / `%X` | Unsigned hexadecimal (lowercase / uppercase) |
| `%%` | Literal percent sign |

### Bonus options

| Option | Description |
|--------|-------------|
| `-` | Left-justify within the field width |
| `0` | Zero-pad (when applicable) |
| `.` + precision | Precision for numbers and strings |
| field width | Minimum field width |
| `#` | Alternate form for hex (`0x` / `0X`) |
| `+` | Always show a sign for signed conversions |
| space | Prefix a space for positive signed values |

---

## Instructions

### Requirements

- A C compiler (`cc`)
- `make`

### Compilation

From the project root:

```bash
make
```

This builds **libft** first, then produces **`libftprintf.a`**.

Other useful rules:

```bash
make clean    # remove object files
make fclean   # remove objects and the library
make re       # fclean + all
make bonus    # same as all (bonus is included in the main build)
```

Compilation flags used: `-Wall -Wextra -Werror`.

### Usage

Link the library in your program:

```bash
cc -Wall -Wextra -Werror your_program.c -L. -lftprintf -o your_program
```

Example:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s!\n", "42");
	ft_printf("Number: %d | Hex: %#x\n", 42, 255);
	ft_printf("Pointer: %p\n", (void *)0);
	return (0);
}
```

---

## Project structure

```
ft_printf/
├── ft_printf.c              # Main function
├── ft_printf.h              # Header and t_format definition
├── ft_format_parser.c       # Format string parsing
├── ft_args_utils.c          # Argument extraction by type
├── ft_printf_utils.c        # Format init and shared helpers
├── ft_char_utils.c          # %c
├── ft_str_utils.c           # %s
├── ft_ptr_utils.c           # %p
├── ft_int_utils.c           # %d / %i
├── ft_int_utils2.c          # Signed int helpers
├── ft_unsignedint_utils.c   # %u
├── ft_hex_utils.c           # %x / %X
├── Makefile
└── libft/                   # Dependency library
```

---

## Resources

### Documentation & references

- [printf(3) — Linux man page](https://man7.org/linux/man-pages/man3/printf.3.html)
- [stdarg — Variable arguments](https://man7.org/linux/man-pages/man3/stdarg.3.html)
- [C11 Standard — Formal grammar of fprintf](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) (section 7.21.6)
- [42 subject: ft_printf](https://cdn.intra.42.fr/) *(intra subject PDF)*
- Tutorials / explanations on format flags, width, and precision (classic printf behavior)

### AI usage

AI assistance was used for the following tasks:

- **Documentation**: drafting and structuring this `README.md` (sections required by the curriculum, wording, and layout).
- **No AI-generated project code** was submitted as a substitute for understanding: the implementation (parser, conversions, flags, Makefile integration with libft) was developed and validated through personal work, testing, and peer discussion.

AI was **not** used to replace reasoning on core concepts (variadic arguments, format parsing, edge cases). When used, it served as a writing/structuring aid for project presentation, not as a source of unchecked solutions.
