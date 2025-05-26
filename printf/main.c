#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

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

int valid_flag_combo(unsigned char flags, FormatSpecifier spec)
{
	int bit;

	bit = 0;
    while ( bit < 7 ) {
        if ((flags & (1 << bit)) && compatibility[spec][bit] == 0)
            return (0);
		++bit;
    }
    return (1);
}

// Map single char to FormatSpecifier enum index
FormatSpecifier parse_specifier(char c)
{
	int i;

	i =0;
    while ( i < 18 )
	{
        if (specifier_str[i][0] == c)
            return ((FormatSpecifier)i);
		i++;
    }
    return (SPEC_UNKNOWN);
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
        return (-1);
    while (isdigit(**p)) {
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    return (val);
}
// Parse integer number or positional index, returns number or -1 if none
// Advances pointer over digits (and $ if positional)
int parse_number_or_positional(const char **p, int *positional) {
    const char *start = *p;
    int val = 0;
    *positional = 0;

    if (!isdigit(**p))
        return (-1);
    while (isdigit(**p)) {
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    if (**p == '$') {
        *positional = val;
        (*p)++;
        return (-1);
    }
    return (val);
}

int ft_percentage_detected(const char *str)
{
	int i;

	i=0;
	if(str[i]=='%' && str[i+1]=='%')
		return (1);
	return (0);
}
int ft_check_width(const char **pp, int *rpos)
{
    const char *p = *pp;
    int width = -1, pos = 0;

    if (*p == '*') {
        p++;
        if (isdigit(*p)) {
            width = parse_number_or_positional(&p, &pos);
            if (pos) *rpos = pos;
        } else {
            width = -2;
        }
    } else {
        width = parse_number_or_positional(&p, rpos);
    }
    *pp = p;
    return width;
}

int ft_check_precision(const char **pp, int *rpos)
{
    const char *p = *pp;
    int precision = -1, pos = 0;

    if (*p == '.') {
        p++;
        if (*p == '*') {
            p++;
            if (isdigit(*p)) {
                precision = parse_number_or_positional(&p, &pos);
                if (pos) *rpos = pos;
            } else {
                precision = -2;
            }
        } else {
            precision = parse_number_or_positional(&p, rpos);
        }
    }

    *pp = p;
    return precision;
}

void print_format_result(const char *fmt, int res[5]) {
    if (res[0]) {
        printf("%s  -> valid (positional width arg #%d)\n", fmt, res[0]);
    } else if (res[1] == -2) {
        printf("%s  -> valid (dynamic width from next arg)\n", fmt);
    } else if (res[2]) {
        printf("%s  -> valid (positional precision arg #%d)\n", fmt, res[2]);
    } else if (res[3] == -2) {
        printf("%s  -> valid (dynamic precision from next arg)\n", fmt);
    } else if (res[4]) {
        printf("%s  -> valid\n", fmt);
    } else {
        printf("%s  -> invalid\n", fmt);
    }
}
void analyze_format(const char *fmt, int result[5]) {
    const char *p = fmt;
    int positional_precision = 0;
    int positional_width = 0;
    int flag;

    // Initialize result array to default values
    // [0] = positional_width, [1] = width
    // [2] = positional_precision, [3] = precision
    // [4] = validity flag
    for (int i = 0; i < 5; i++)
        result[i] = 0;

    if (*p != '%') {
        // Not a format string
        flag = 0;
        result[1] = -1; // no width
        result[3] = -1; // no precision
        result[4] = flag;
        return;
    }

    p++; // skip '%'
    unsigned char flags = parse_flags(&p);
    int width = ft_check_width(&p, &positional_width);
    int precision = ft_check_precision(&p, &positional_precision);
    LengthModifier length = parse_length(&p);
    FormatSpecifier spec = parse_specifier(*p);
    if (spec != SPEC_UNKNOWN)
        p++; // move past specifier if recognized

    if (spec != SPEC_UNKNOWN && valid_flag_combo(flags, spec))
        flag = 1;  // valid
    else
        flag = 0;  // invalid

    result[0] = positional_width;
    result[1] = width;
    result[2] = positional_precision;
    result[3] = precision;
    result[4] = flag;
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


// int main() {
//     const char *formats[] = {
//         "%10.2ld",
//         "%10.2lo",
//         "%10.2lx",
//         "%10.2lf",
//         "%10.2le",
//         "%10.2lc",
//         "%10.2ls",
//         "%+10.2ld",
//         "%+10.2lf",
//         "%+10.2le",
//         "%-+10.2ld",
//         "%-+10.2lf",
//         "%-+10.2le",
//         "%#010.2lo",
//         "%#010.2lx",
//         "%#010.2lf",
//         "%#010.2le",
//         "% 10.2ld",
//         "%#+10.2lf",
//         "%#+10.2le",

//         // Added examples:
//         "%#8x",          // hash with hex
//         "%-20s",         // left align string
//         "%0+5.3d",       // zero pad, plus flag, width and precision
//         "%'15.4f",       // tick flag, width, precision
//         "%I10u",         // I flag with unsigned decimal
//         "%zhd",          // length z with h and d
//         "%llX",          // long long and capital X
//         "%jIo",          // j length, I flag, octal
//         "%-#12.6a",      // left, hash, width, precision, hex float
//         "%+ .3g",        // plus, space flags, precision
//         "%0#8.4E",       // zero pad, hash, width, precision, capital E
//         "%tX",           // t length, capital X
//         "%+n",           // plus flag with n specifier (odd but test)
//         "%#0- +'I12.5f", // all flags combined with width and precision and I flag
//         "%hd",          // short int
//         "%hi",          // short int (alternate)
//         "%ho",          // short unsigned octal
//         "%hx",          // short unsigned hex
//         "%hX",          // short unsigned hex (uppercase)
//         "%hu",          // short unsigned int

//         "%hhd",         // signed char
//         "%hhi",         // signed char
//         "%hhu",         // unsigned char
//         "%hhx",         // unsigned char hex
//         "%hhX",         // unsigned char hex (uppercase)

//         "%+5.2hd",      // short int with flags
//         "%#06hhx",      // unsigned char hex with flags and width



//         // New tests with * and positional
//         "%*d",             // dynamic width
//         "%.*f",            // dynamic precision
//         "%*.*f",           // dynamic width and precision
//         "%3$*2$.*1$f",     // positional width/precision/value
//         "%2$.*3$d",        // positional precision and value
//         "%1$*d",           // positional width only (invalid form, but allowed)
//         "%*10$d",          // dynamic width then positional specifier (weird but testing)
//         "%10$.*2$f",       // positional width (invalid - width must be number or *)
//         "%110$.*2$f",       // same as above but testing parser robustness
//     };

//     int n = sizeof(formats) / sizeof(formats[0]);
//     for (int i = 0; i < n; i++) {
//         analyze_format(formats[i]);
//     }



//     const char *test_strings[] = {
//         "Hello, world!",                             // no format specifiers
//         "Value: %d",                                 // simple integer specifier
//         "Float: %10.2f",                             // width and precision
//         "Literal percent: %%",                        // literal %
//         "Multiple: %dx, %s, and %0#8x",               // multiple specifiers with flags
//         "Incomplete: %",                             // incomplete specifier
//         "Percent then text %% followed by %u",       // mixed literal % and specifier
//         "Complex: %-+10.3Lf",                        // flags, width, precision, length modifier
//         "Weird: %I10d",                             // unsupported length modifier 'I'
//         "Escaped percent %%%d",                      // tricky literal percent then format
//     };

//    n = sizeof(test_strings) / sizeof(test_strings[0]);

//     for (int i = 0; i < n; i++) {
//         printf("Input: \"%s\"\n", test_strings[i]);
//         parse_full_string(test_strings[i]);
//         printf("\n");
//     }
//     return 0;
// }

typedef struct Node {
    char *text;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void init_list(List *list) {
    list->head = NULL;
    list->tail = NULL;
}

void append_to_list(List *list, const char *str, int start, int end) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("malloc");
        exit(1);
    }
    int len = end - start;
    new_node->text = malloc(len + 1);
    if (!new_node->text) {
        perror("malloc");
        exit(1);
    }
    strncpy(new_node->text, str + start, len);
    new_node->text[len] = '\0';
    new_node->next = NULL;
    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
}

void print_list(const List *list, const char *label) {
	int result[5];
    Node *cur = list->head;
    printf("%s:\n", label);
    while (cur) {
        printf("  %s\n", cur->text);
		analyze_format(cur->text, result);
		print_format_result(cur->text, result);
        cur = cur->next;
    }
    printf("\n");
}

void free_list(List *list) {
    Node *cur = list->head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;

        free(tmp->text);
        free(tmp);
    }
    list->head = list->tail = NULL;
}

void	parse_printf_string(const char *str, List *parts,
		List *format)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	j = 0;
	b = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (b != i)
				append_to_list(parts, str, b, i);
			j = i + 1;
			while (str[j] && !strchr("diouxXfFeEgGaAcspn%", str[j]))
				j++;
			if (str[j])
			{
				append_to_list(format, str, i, j + 1);
				i = j + 1;
				b = i;
				continue ;
			}
		}
		i++;
	}
	if (b < i)
		append_to_list(parts, str, b, i);
}

int main() {
    const char str[] = "This is a test with %d values and %% signs and %10.2f floats.";
	const char *test_str =
	    "Integer: %d, Unsigned: %u, Octal: %o, Hex (lower): %x, Hex (upper): %X, "
	    "Char: %c, String: %s, Pointer: %p, Float: %f, Scientific (lower): %e, "
	    "Scientific (upper): %E, Shortest (lower): %g, Shortest (upper): %G, "
	    "Hex float (lower): %a, Hex float (upper): %A, "
	    "Write count: %n, Percent sign: %%, "
	    "With width: %10d, With precision: %.3f, Width and precision: %8.2f, "
	    "Left justified: %-10s, Zero padded: %05d, "
	    "Long modifier: %ld, Short modifier: %hd, Long long: %lld, "
	    "Size_t: %zu, Intmax_t: %jd, Ptrdiff_t: %td, "
	    "Custom format: %*.*f, Broken: %q, Mix: %+-#08.3lld.";
    List to_check, to_skip;
    init_list(&to_check);
    init_list(&to_skip);

    parse_printf_string(test_str, &to_skip, &to_check);

    // print_list(&to_skip, "Plain Text (Skip)");
    print_list(&to_check, "Format Specifiers (Check)");

    free_list(&to_skip);
    free_list(&to_check);

    return 0;
}


typedef enum {
    TYPE_SINT     = 0x01,
    TYPE_UINT     = 0x02,
    TYPE_FLOAT    = 0x03,
    TYPE_CHARSTR  = 0x04,
    TYPE_PTR      = 0x05,
    TYPE_SPECIAL  = 0x06,
    TYPE_PERCENT  = 0x07
} SpecTypeCode;

void handle_sint(const char *fmt)    { printf("Handling signed int: %s\n", fmt); }
void handle_uint(const char *fmt)    { printf("Handling unsigned int: %s\n", fmt); }
void handle_float(const char *fmt)   { printf("Handling float: %s\n", fmt); }
void handle_charstr(const char *fmt) { printf("Handling char/string: %s\n", fmt); }
void handle_ptr(const char *fmt)     { printf("Handling pointer: %s\n", fmt); }
void handle_special(const char *fmt) { printf("Handling special: %s\n", fmt); }
void handle_percent(const char *fmt) { printf("Handling percent: %s\n", fmt); }
typedef void (*FormatHandler)(const char *fmt);

void process_format(const char *fmt, SpecTypeCode type) {
    switch (type) {
        case TYPE_SINT:
            handle_sint(fmt);
            break;
        case TYPE_UINT:
            handle_uint(fmt);
            break;
        case TYPE_FLOAT:
            handle_float(fmt);
            break;
        case TYPE_CHARSTR:
            handle_charstr(fmt);
            break;
        case TYPE_PTR:
            handle_ptr(fmt);
            break;
        case TYPE_SPECIAL:
            handle_special(fmt);
            break;
        case TYPE_PERCENT:
            handle_percent(fmt);
            break;
        default:
            printf("Unknown type: %s\n", fmt);
    }
}
