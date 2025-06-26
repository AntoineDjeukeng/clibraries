

# `printf` Format String Summary

## General Syntax

The `printf` format string consists of a sequence of characters that specify how to format the output. Each format specifier begins with `%` and is followed by components (some optional), in this specific order:

### `%[flags][width][.precision][length]specifier`

---

## 1. Flags

<table>
<thead>
<tr>
  <th>Flag</th><th>Meaning</th><th>Notes</th>
</tr>
</thead>
<tbody>
<tr><td><code>#</code></td><td>Alternate form (e.g., <code>0x</code> for hex, always shows <code>.</code> for floats)</td><td>Affects <code>%o</code>, <code>%x</code>, <code>%X</code>, <code>%a</code>, <code>%A</code>, <code>%e</code>, <code>%f</code>, <code>%g</code></td></tr>
<tr><td><code>0</code></td><td>Pads numbers with leading zeroes</td><td>Ignored if <code>-</code> or precision is set</td></tr>
<tr><td><code>-</code></td><td>Left-align within the given field width</td><td>Overrides <code>0</code></td></tr>
<tr><td><code>(space)</code></td><td>Prefix positive numbers with space</td><td>Ignored if <code>+</code> is used</td></tr>
<tr><td><code>+</code></td><td>Always prefix numbers with a sign (<code>+</code> or <code>-</code>)</td><td>Overrides space flag</td></tr>
<tr><td><code>'</code></td><td>Group thousands using locale (e.g., 1,000,000)</td><td>Requires <code>setlocale()</code> and <code>%'d</code>, <code>%'f</code>, etc.</td></tr>
<tr><td><code>I</code></td><td>Use locale-specific digits (e.g., Arabic-Indic in Persian locale)</td><td>Locale-sensitive for <code>%d</code>, <code>%i</code>, <code>%u</code></td></tr>
</tbody>
</table>

<br/>

<table>
<thead>
<tr>
<th>Flag</th><th>d,i</th><th>o</th><th>u</th><th>x,X</th><th>a,A,e,E,f,F,g,G</th><th>c</th><th>s</th><th>p</th><th>n</th>
</tr>
</thead>
<tbody>
<tr>
<td><code>#</code></td>
<td style="color:#d32f2f;">✘</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td>
</tr>
<tr>
<td><code>0</code></td>
<td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#388e3c;">✔</td>
</tr>
<tr>
<td><code>-</code></td>
<td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td>
</tr>
<tr>
<td><code>(space)</code></td>
<td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td>
</tr>
<tr>
<td><code>+</code></td>
<td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td>
</tr>
<tr>
<td><code>'</code></td>
<td style="color:#fbc02d;">⚠</td><td style="color:#fbc02d;">⚠</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#fbc02d;">⚠</td><td style="color:#fbc02d;">⚠</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td>
</tr>
<tr>
<td><code>I</code></td>
<td style="color:#fbc02d;">⚠</td><td style="color:#fbc02d;">⚠</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td>
</tr>
</tbody>
</table>

---

## 2. Field Width

| Syntax | Meaning                                                 | Example                                |
| ------ | ------------------------------------------------------- | -------------------------------------- |
| `5`    | Minimum width of 5 characters                           | `%5d` → `'   42'`                      |
| `*`    | Width taken from next argument                          | `printf("%*d", 5, 42)` → `'   42'`     |
| `*m$`  | Width from m-th argument (1-based positional parameter) | `printf("%2$*1$d", 5, 42)` → `'   42'` |
| `-5`   | Left-justify, same as `%-5d`                            | `'42   '`                              |

---

<table>
<thead>
<tr>
<th>Feature</th><th>d,i</th><th>o,u,x,X</th><th>a,A,e,E,f,F,g,G</th><th>c</th><th>s</th><th>p</th><th>n</th>
</tr>
</thead>
<tbody>
<tr>
<td>Width</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td>
</tr>
<tr>
<td>Precision</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td>
</tr>
<tr>
<td>Width as <code>*</code></td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td>
</tr>
<tr>
<td>Precision as <code>*</code></td><td style="color:#388e3c;">✔</td><td style="color:#388e3c;">✔</td><td style="color:#388e


3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#388e3c;">✔</td><td style="color:#d32f2f;">✘</td><td style="color:#d32f2f;">✘</td>

</tr>
</tbody>
</table>

---

## 3. Precision

* For **integers** (`d, i, o, u, x, X`): minimum number of digits; pads with leading zeroes if needed.
* For **floating point** (`a, A, e, E, f, F, g, G`): number of digits after decimal point.
* For **strings** (`s`): maximum number of characters printed.
* For **characters** (`c`) and pointers (`p`), precision is ignored.

---

## 4. Length Modifiers

| Modifier | Meaning                             | Example      | Notes                                |
| -------- | ----------------------------------- | ------------ | ------------------------------------ |
| `hh`     | `signed char` or `unsigned char`    | `%hhd`       | 8-bit integer                        |
| `h`      | `short` or `unsigned short`         | `%hd`        | 16-bit integer                       |
| `l`      | `long` or `unsigned long`           | `%ld`, `%lu` | 32-bit or 64-bit depends on platform |
| `ll`     | `long long` or `unsigned long long` | `%lld`       | 64-bit integer                       |
| `j`      | `intmax_t` or `uintmax_t`           | `%jd`        | Maximum width integer type           |
| `z`      | `size_t`                            | `%zd`        | Size type                            |
| `t`      | `ptrdiff_t`                         | `%td`        | Pointer difference                   |
| `L`      | `long double`                       | `%Lf`        | Long double float                    |

---

## 5. Conversion Specifiers

| Specifier | Meaning                                  | Example    | Notes                                                |
| --------- | ---------------------------------------- | ---------- | ---------------------------------------------------- |
| `d`, `i`  | Signed decimal integer                   | `%d`, `%i` |                                                      |
| `o`       | Unsigned octal integer                   | `%o`       |                                                      |
| `u`       | Unsigned decimal integer                 | `%u`       |                                                      |
| `x`       | Unsigned hexadecimal integer (lowercase) | `%x`       |                                                      |
| `X`       | Unsigned hexadecimal integer (uppercase) | `%X`       |                                                      |
| `f`, `F`  | Decimal floating-point                   | `%f`       | Includes `nan`, `inf` support                        |
| `e`, `E`  | Scientific notation (mantissa/exponent)  | `%e`       |                                                      |
| `g`, `G`  | Use `%e` or `%f` based on value          | `%g`       | Removes trailing zeros                               |
| `a`, `A`  | Hexadecimal floating-point               | `%a`       | Hexadecimal float output                             |
| `c`       | Character                                | `%c`       | Prints a single character                            |
| `s`       | String                                   | `%s`       | Prints characters up to precision or null-terminated |
| `p`       | Pointer address                          | `%p`       | Implementation-defined format                        |
| `n`       | Number of characters printed so far      | `%n`       | Writes to an integer pointer                         |
| `%`       | Literal `%`                              | `%%`       | Prints a `%` character                               |

---

## 6. Examples

```c
printf("%08x", 305419896);    // 8 chars, zero padded: 12345678 → 12345678
printf("%-10s", "hello");     // left aligned string: "hello     "
printf("%+.2f", 3.14159);     // always show sign, 2 decimals: +3.14
printf("%#x", 255);           // alternate form hex: 0xff
printf("%'d", 1000000);       // grouped thousands (locale): 1,000,000
printf("%*.*f", 8, 3, 3.14159); // width 8, precision 3: "   3.142"
```

---

If you want me to generate this as a **PDF**, **HTML** page, or **LaTeX table**, just ask!
