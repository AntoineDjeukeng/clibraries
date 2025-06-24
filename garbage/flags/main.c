#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define FLAG_HASH   (1 << 0)
#define FLAG_ZERO   (1 << 1)
#define FLAG_MINUS  (1 << 2)
#define FLAG_SPACE  (1 << 3)
#define FLAG_PLUS   (1 << 4)
#define FLAG_TICK   (1 << 5)
#define FLAG_I      (1 << 6)

const char flag_chars[7] = { '#', '0', '-', ' ', '+', '\'', 'I' };

typedef enum {
    LEN_NONE, LEN_H, LEN_HH, LEN_L, LEN_LL, LEN_CAPL, LEN_Z, LEN_J, LEN_T
} LengthModifier;

typedef enum {
    SPEC_D, SPEC_I, SPEC_O, SPEC_U,
    SPEC_X, SPEC_X_CAP, SPEC_F, SPEC_F_CAP,
    SPEC_E, SPEC_E_CAP, SPEC_G, SPEC_G_CAP,
    SPEC_A, SPEC_A_CAP, SPEC_C, SPEC_S, SPEC_P, SPEC_N,
    SPEC_UNKNOWN = -1
} FormatSpecifier;

const char *specifier_str[] = {
    "d", "i", "o", "u", "x", "X", "f", "F",
    "e", "E", "g", "G", "a", "A", "c", "s", "p", "n"
};

const char *length_str[] = {
    "", "h", "hh", "l", "ll", "L", "z", "j", "t"
};

int compatibility[18][7] = {
    // #  0  -  space +  '  I
    { 0, 1, 1, 1, 1, 2, 2 },  // d
    { 0, 1, 1, 1, 1, 2, 2 },  // i
    { 1, 1, 1, 0, 0, 2, 2 },  // o
    { 0, 1, 1, 0, 0, 2, 2 },  // u
    { 1, 1, 1, 0, 0, 2, 2 },  // x
    { 1, 1, 1, 0, 0, 2, 2 },  // X
    { 1, 1, 1, 0, 1, 2, 0 },  // f
    { 1, 1, 1, 0, 1, 2, 0 },  // F
    { 1, 1, 1, 0, 1, 2, 0 },  // e
    { 1, 1, 1, 0, 1, 2, 0 },  // E
    { 1, 1, 1, 0, 1, 2, 0 },  // g
    { 1, 1, 1, 0, 1, 2, 0 },  // G
    { 1, 1, 1, 0, 1, 2, 0 },  // a
    { 1, 1, 1, 0, 1, 2, 0 },  // A
    { 0, 0, 1, 0, 0, 0, 0 },  // c
    { 0, 0, 1, 0, 0, 0, 0 },  // s
    { 0, 1, 1, 0, 0, 0, 0 },  // p
    { 0, 0, 0, 0, 0, 0, 0 },  // n
};

int valid_flag_combo(unsigned char flags, FormatSpecifier spec) {
    for (int bit = 0; bit < 7; ++bit) {
        if ((flags & (1 << bit)) && compatibility[spec][bit] == 0) {
            return 0;
        }
    }
    return 1;
}

// Map single char to FormatSpecifier enum index
FormatSpecifier parse_specifier(char c) {
    for (int i = 0; i < 18; i++) {
        if (specifier_str[i][0] == c)
            return (FormatSpecifier)i;
    }
    return SPEC_UNKNOWN;
}

int get_length_modifier(const char **p,char match) 
{
     if (**p == match) 
    { 
        (*p)++; 
        return (1);
    }
    return (0);
}

LengthModifier parse_length(const char **p) {
    if (get_length_modifier(p, 'h')) {
        if (get_length_modifier(p, 'h'))
            return (LEN_HH);
        return (LEN_H);
    }
    else if (get_length_modifier(p, 'l')) {
        if (get_length_modifier(p, 'l')) 
            return (LEN_LL);
        return (LEN_L);
    }
    else if (get_length_modifier(p, 'L'))
        return (LEN_CAPL);
    else if (get_length_modifier(p, 'z'))
        return (LEN_Z);
    else if (get_length_modifier(p, 'j'))
        return (LEN_J);
    else if (get_length_modifier(p, 't'))
        return (LEN_T);
    return (LEN_NONE);
}

// Parse flags string into bitmask
unsigned char parse_flags(const char **p) {
    unsigned char flags;
    int found;
    int i;

    flags = 0;
    found = 1;
    while (found) {
        found = 0;
        i = 0;
        while (i < 7) {
            if (**p == flag_chars[i]) {
                flags = flags | (1 << i);
                (*p)++;
                found = 1;
                break;
            }
            i++;
        }
    }
    return (flags);
}

// Parse integer number from string (width or precision)
int parse_number(const char **p) {
    int val = 0;
    if (!isdigit(**p))
        return -1;
    while (isdigit(**p)) {
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    return val;
}
// Parse integer number or positional index, returns number or -1 if none
// Advances pointer over digits (and $ if positional)
int parse_number_or_positional(const char **p, int *positional) {
    const char *start = *p;
    int val = 0;
    *positional = 0;

    if (!isdigit(**p))
        return -1;

    while (isdigit(**p)) {
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    if (**p == '$') {
        *positional = val;
        (*p)++;
        return -1; // Return -1 to indicate this was positional specifier, not width/precision
    }
    return val;
}

// Updated analyze_format to support * and positional indexes
void analyze_format(const char *fmt) {
    const char *p = fmt;

    if (*p != '%') {
        printf("Not a format string: %s\n", fmt);
        return;
    }
    p++; // skip '%'

    unsigned char flags = parse_flags(&p);

    int width = -1;
    int positional_width = 0;

    // Check for width: number or '*', possibly with positional
    if (*p == '*') {
        p++;
        // Check for positional argument for width
        if (isdigit(*p)) {
            int pos = 0;
            width = parse_number_or_positional(&p, &pos);
            if (pos) positional_width = pos;
        } else {
            width = -2; // -2 to mark dynamic width from next arg (no positional)
        }
    } else {
        width = parse_number_or_positional(&p, &positional_width);
    }

    int precision = -1;
    int positional_precision = 0;
    if (*p == '.') {
        p++;
        if (*p == '*') {
            p++;
            if (isdigit(*p)) {
                int pos = 0;
                precision = parse_number_or_positional(&p, &pos);
                if (pos) positional_precision = pos;
            } else {
                precision = -2; // dynamic precision without positional
            }
        } else {
            precision = parse_number_or_positional(&p, &positional_precision);
        }
    }

    LengthModifier length = parse_length(&p);

    FormatSpecifier spec = parse_specifier(*p);
    if (spec == SPEC_UNKNOWN) {
        printf("Unknown specifier in format: %s\n", fmt);
        return;
    }
    p++; // advance past specifier

    // Just show info about positional width and precision if any
    if (positional_width)
        printf("%s  -> valid (positional width arg #%d)\n", fmt, positional_width);
    else if (width == -2)
        printf("%s  -> valid (dynamic width from next arg)\n", fmt);
    else if (positional_precision)
        printf("%s  -> valid (positional precision arg #%d)\n", fmt, positional_precision);
    else if (precision == -2)
        printf("%s  -> valid (dynamic precision from next arg)\n", fmt);
    else if (valid_flag_combo(flags, spec)) {
        printf("%s  -> valid\n", fmt);
    } else {
        printf("%s  -> invalid\n", fmt);
    }
}
void parse_full_string(const char *str) {
    for (int i = 0; str[i] != '\0';) {
        if (str[i] == '%') {
            if (str[i+1] == '%') {
                // literal percent
                putchar('%');
                i += 2;
            } else {
                // parse format command starting at str[i]
                const char *start = &str[i];
                int j = i + 1;

                // Find end of format specifier (the conversion char)
                // For simplicity, let's scan until we find a specifier character
                while (str[j] != '\0' && !strchr("diouxXfFeEgGaAcspn%", str[j])) {
                    j++;
                }

                if (str[j] != '\0') {
                    j++;  // include the specifier character

                    // Now substring from i to j-1 is a full format command
                    char format_command[64] = {0};
                    int len = j - i;
                    if (len < sizeof(format_command)) {
                        memcpy(format_command, &str[i], len);
                        format_command[len] = '\0';

                        printf("Detected format command: %s\n", format_command);
                        // You can call analyze_format(format_command) here
                    }
                    i = j;  // move past the command
                } else {
                    // malformed or incomplete format command at the end
                    i++;
                }
            }
        } else {
            putchar(str[i]);
            i++;
        }
    }
}


int main() {
    const char *formats[] = {
        "%10.2ld",
        "%10.2lo",
        "%10.2lx",
        "%10.2lf",
        "%10.2le",
        "%10.2lc",
        "%10.2ls",
        "%+10.2ld",
        "%+10.2lf",
        "%+10.2le",
        "%-+10.2ld",
        "%-+10.2lf",
        "%-+10.2le",
        "%#010.2lo",
        "%#010.2lx",
        "%#010.2lf",
        "%#010.2le",
        "% 10.2ld",
        "%#+10.2lf",
        "%#+10.2le",

        // Added examples:
        "%#8x",          // hash with hex
        "%-20s",         // left align string
        "%0+5.3d",       // zero pad, plus flag, width and precision
        "%'15.4f",       // tick flag, width, precision
        "%I10u",         // I flag with unsigned decimal
        "%zhd",          // length z with h and d
        "%llX",          // long long and capital X
        "%jIo",          // j length, I flag, octal
        "%-#12.6a",      // left, hash, width, precision, hex float
        "%+ .3g",        // plus, space flags, precision
        "%0#8.4E",       // zero pad, hash, width, precision, capital E
        "%tX",           // t length, capital X
        "%+n",           // plus flag with n specifier (odd but test)
        "%#0- +'I12.5f", // all flags combined with width and precision and I flag
        "%hd",          // short int
        "%hi",          // short int (alternate)
        "%ho",          // short unsigned octal
        "%hx",          // short unsigned hex
        "%hX",          // short unsigned hex (uppercase)
        "%hu",          // short unsigned int

        "%hhd",         // signed char
        "%hhi",         // signed char
        "%hhu",         // unsigned char
        "%hhx",         // unsigned char hex
        "%hhX",         // unsigned char hex (uppercase)

        "%+5.2hd",      // short int with flags
        "%#06hhx",      // unsigned char hex with flags and width



        // New tests with * and positional
        "%*d",             // dynamic width
        "%.*f",            // dynamic precision
        "%*.*f",           // dynamic width and precision
        "%3$*2$.*1$f",     // positional width/precision/value
        "%2$.*3$d",        // positional precision and value
        "%1$*d",           // positional width only (invalid form, but allowed)
        "%*10$d",          // dynamic width then positional specifier (weird but testing)
        "%10$.*2$f",       // positional width (invalid - width must be number or *)
        "%110$.*2$f",       // same as above but testing parser robustness
    };

    int n = sizeof(formats) / sizeof(formats[0]);
    for (int i = 0; i < n; i++) {
        analyze_format(formats[i]);
    }



    const char *test_strings[] = {
        "Hello, world!",                             // no format specifiers
        "Value: %d",                                 // simple integer specifier
        "Float: %10.2f",                             // width and precision
        "Literal percent: %%",                        // literal %
        "Multiple: %d, %s, and %0#8x",               // multiple specifiers with flags
        "Incomplete: %",                             // incomplete specifier
        "Percent then text %% followed by %u",       // mixed literal % and specifier
        "Complex: %-+10.3Lf",                        // flags, width, precision, length modifier
        "Weird: %I10d",                             // unsupported length modifier 'I'
        "Escaped percent %%%d",                      // tricky literal percent then format
    };

   n = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < n; i++) {
        printf("Input: \"%s\"\n", test_strings[i]);
        parse_full_string(test_strings[i]);
        printf("\n");
    }
    return 0;
}
