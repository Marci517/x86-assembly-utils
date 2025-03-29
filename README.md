# Assembly Projects – String and Number Operations (32-bit)

## Overview

This project consists of NASM x86 (32-bit) Assembly programs that implement custom string and number manipulation modules, along with interactive demo programs. The goal is to understand low-level data handling, including user input processing, string operations, and base conversions without relying on standard libraries.

All programs were tested and debugged using **OllyDbg**. Only the **32-bit** version of the task was implemented.

> The only external include file used is `mio.inc`, which provides basic input/output routines (e.g., character I/O). This file was provided and not written as part of the project.


---

## Modules

### 1. `IONUM.ASM` / `IONUM.INC` – Number Input/Output

Contains routines to read and write 32-bit signed integers, hexadecimal, and binary numbers. All input ends on `<Enter>`. Backspace is handled correctly. Overflow and invalid input are detected and indicated via the **Carry Flag (CF)**.

- `ReadInt()` → `EAX`: Reads a signed 32-bit decimal integer.
- `WriteInt(EAX)`: Outputs a signed 32-bit decimal integer.
- `ReadHex()` → `EAX`: Reads an unsigned 32-bit hexadecimal number (accepts both uppercase and lowercase).
- `WriteHex(EAX)`: Prints a 32-bit number in hexadecimal format with `0x` prefix.
- `ReadBin()` → `EAX`: Reads an unsigned 32-bit binary number.
- `WriteBin(EAX)`: Prints a 32-bit binary number, grouped by 4 bits with spaces.

Error handling is performed in the main program if CF=1 after a read.

---

### 2. `IOSTR.ASM` / `IOSTR.INC` – String Input/Output

Handles proper string reading with **backspace support**, ensuring the cursor moves back and deletes characters visually. Inputs terminate on `<Enter>`.

- `ReadStr(ESI/EDI, ECX)`: Reads a null-terminated C-style string.
- `ReadLnStr(ESI/EDI, ECX)`: Same as `ReadStr`, but prints a newline after input.
- `WriteStr(ESI)`: Outputs a null-terminated string.
- `WriteLnStr(ESI)`: Same as `WriteStr`, but adds a newline.
- `NewLine()`: Moves the cursor to a new line.

---

### 3. `STRINGS.ASM` / `STRINGS.INC` – String Operations

Provides utilities for operating on null-terminated strings in memory.

- `StrLen(ESI)` → `EAX`: Returns the length of the string.
- `StrCat(EDI, ESI)`: Concatenates `ESI` to the end of `EDI`.
- `StrUpper(ESI)`: Converts all lowercase characters to uppercase.
- `StrLower(ESI)`: Converts all uppercase characters to lowercase.
- `StrCompact(ESI, EDI)`: Copies from `ESI` to `EDI`, removing spaces, tabs, carriage returns, and newlines.

---

## Example Programs

### `IOPELDA.ASM` – Number Input/Output Demo

Demonstrates reading and displaying 32-bit values in decimal, hexadecimal, and binary. Each read is followed by output in three formats. Overflow, invalid characters, and backspace are all handled.

Program steps:
1. Read a signed 32-bit integer (decimal).
2. Print it in:
   - Decimal (signed)
   - Hexadecimal (two's complement)
   - Binary (two's complement)
3. Read a 32-bit hexadecimal number.
4. Print it in all three formats.
5. Read a 32-bit binary number.
6. Print it in all three formats.
7. Print the **sum** of the three values in all formats.

---

### `STRPELDA.ASM` – String Operation Demo

Demonstrates all string operations with user interaction.

Program steps:
1. Prompt and read the first string.
2. Display:
   - Its length
   - Its compacted version
   - The compacted version in lowercase
3. Prompt and read the second string.
4. Display:
   - Its length
   - Its compacted version
   - The compacted version in uppercase
5. Create a new string:
   - First string converted to uppercase
   - Second string converted to lowercase
   - Concatenate them
6. Print the new string and its length.

---

## Notes

- All strings are **null-terminated (C-style)**.
- All number representations use **two's complement format**.
- Only the **32-bit implementation** is included.
- Debugging was performed using **OllyDbg**.
- Designed to run in a DOS-compatible environment or emulator.
