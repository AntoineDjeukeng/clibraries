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
const char *length_str[] = {
    "", "h", "hh", "l", "ll", "L", "z", "j", "t"
};
typedef enum {
    SPEC_D, SPEC_I, SPEC_O, SPEC_U,
    SPEC_X, SPEC_X_CAP, SPEC_F, SPEC_F_CAP,
    SPEC_E, SPEC_E_CAP, SPEC_G, SPEC_G_CAP,
    SPEC_A, SPEC_A_CAP, SPEC_C, SPEC_S, SPEC_P, SPEC_N,
    SPEC_UNKNOWN = -1
} FormatSpecifier;

typedef struct {
    const char *str;
    int len;
    LengthModifier mod;
} LengthMap;

LengthModifier parse_length(const char **p) {
	int i;

	static const LengthMap table[] = {
	    {"hh", 2, LEN_HH},
	    {"ll", 2, LEN_LL},
	    {"h",  1, LEN_H},
	    {"l",  1, LEN_L},
	    {"L",  1, LEN_CAPL},
	    {"z",  1, LEN_Z},
	    {"j",  1, LEN_J},
	    {"t",  1, LEN_T},
	    {NULL, 0, LEN_NONE}
	};
	i = 0;
	//fix this
    while ( table[i].str )
	{
        if (strncmp(*p, table[i].str, table[i].len) == 0)
		{
            *p += table[i].len;
            return (table[i].mod);
        }
		i++;
    }
    return (LEN_NONE);
}




const char *specifier_str[] = {
    "d", "i", "o", "u", "x", "X", "f", "F",
    "e", "E", "g", "G", "a", "A", "c", "s", "p", "n"
};



#define HAS_WIDTH          0x01
#define HAS_DYNAMIC_WIDTH  0x02
#define HAS_POSITIONAL_ARG 0x04
#define HAS_WIDTH_POSITION 0x08
#define HAS_PRECISION          0x01
#define HAS_DYNAMIC_PRECISION  0x02
#define HAS_PRECISION_POSITION 0x08

typedef struct {
    int arg_position;
    int width_position;
    int width_value;
    int flags;
    int type;
} width;

typedef struct {
    int arg_position;
    int precision_position;
    int precision_value;
    int flags;
} precision;

typedef struct Node {
    char *text;
    char *format;
    width width;
    precision precision;
    char valide;
    int lout;
    char *output;
    unsigned char flags;
    LengthModifier length;
    FormatSpecifier spec;
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

unsigned char parse_flags(const char **p)
{
    unsigned char flags = 0;
    int found = 1, i;
    while (found) {
        found = 0;
		i =0;
        while (i < 7) {
            if (**p == flag_chars[i]) {
                flags |= (1 << i);
                (*p)++;
                found = 1;
                break;
            }
			i++;
        }
    }
    return flags;
}

int parse_number_or_positional(const char **p, int *positional) {
    const char *start;
    int val;

    start = *p;
    val = 0;
    *positional = 0;
	//fix this
    if (!isdigit(**p))
		return (-1);
    while (isdigit(**p))
	{
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    if (**p == '$')
	{
        *positional = val;
        (*p)++;
        return (-1);
    }
    return (val);
}

void ft_handle_asterisk_width(const char **pp, width *result) {
    const char *p;
    int pos;
    const char *before;
    int dummy;

	p = *pp;
    result->flags |= HAS_WIDTH | HAS_DYNAMIC_WIDTH;
    p++;
	//fix this
    if (isdigit(*p))
	{
        pos = 0;
        before = p;
        result->arg_position = -1;
        dummy = parse_number_or_positional(&p, &pos);
        if (pos > 0)
		{
            result->width_position = pos;
            result->flags |= HAS_WIDTH_POSITION;
        }
		else
            p = before;
    }
    *pp = p;
}

void ft_handle_numeric_width(const char **pp, width *result) {
    const char *p;
    int pos;
    int val;

    p = *pp;
    pos = 0;
    val = parse_number_or_positional(&p, &pos);
    if (val >= 0) {
        result->width_value = val;
        result->flags |= HAS_WIDTH;
    }
    result->arg_position = -1;
    if (pos > 0) {
        result->arg_position = pos;
        result->flags |= HAS_POSITIONAL_ARG;
    }
    *pp = p;
}

const char *get_expected_type_SPEC_d_i(LengthModifier len) {
    switch (len) {
        case LEN_HH: return "signed char";
        case LEN_H:  return "short";
        case LEN_L:  return "long";
        case LEN_LL: return "long long";
        case LEN_J:  return "intmax_t";
        case LEN_Z:  return "ssize_t";
        case LEN_T:  return "ptrdiff_t";
        default:     return "int";
    }
}

typedef enum {
    TYPE_SIGNED_CHAR,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_LONG_LONG,
    TYPE_INTMAX_T,
    TYPE_SSIZE_T,
    TYPE_PTRDIFF_T,
    TYPE_UNSIGNED_CHAR,
    TYPE_UNSIGNED_SHORT,
    TYPE_UNSIGNED_INT,
    TYPE_UNSIGNED_LONG,
    TYPE_UNSIGNED_LONG_LONG,
    TYPE_UINTMAX_T,
    TYPE_SIZE_T,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE,
    TYPE_SIGNED_CHAR_PTR,
    TYPE_SHORT_PTR,
    TYPE_INT_PTR,
    TYPE_LONG_PTR,
    TYPE_LONG_LONG_PTR,
    TYPE_INTMAX_T_PTR,
    TYPE_SIZE_T_PTR,
    TYPE_PTRDIFF_T_PTR,
    TYPE_WINT_T,
    TYPE_WCHAR_T_PTR,
    TYPE_CHAR_PTR,
    TYPE_VOID_PTR,
    TYPE_UNKNOWN,

    TYPE_COUNT 
} ExpectedTypeID;


const char *get_expected_type_SPEC_u_o_x_X(LengthModifier len) {
    switch (len) {
        case LEN_HH: return "unsigned char";
        case LEN_H:  return "unsigned short";
        case LEN_L:  return "unsigned long";
        case LEN_LL: return "unsigned long long";
        case LEN_J:  return "uintmax_t";
        case LEN_Z:  return "size_t";
        case LEN_T:  return "ptrdiff_t";
        default:     return "unsigned int";
    }
}

const char *get_expected_type_SPEC_a_A(LengthModifier len) {
    return (len == LEN_CAPL) ? "long double" : "double";
}

const char *get_expected_type_SPEC_n(LengthModifier len) {
    switch (len) {
        case LEN_HH: return "signed char *";
        case LEN_H:  return "short *";
        case LEN_L:  return "long *";
        case LEN_LL: return "long long *";
        case LEN_J:  return "intmax_t *";
        case LEN_Z:  return "size_t *";
        case LEN_T:  return "ptrdiff_t *";
        default:     return "int *";
    }
}

const char *get_expected_type(FormatSpecifier spec, LengthModifier len) {
    switch (spec) {
        case SPEC_D: case SPEC_I:
            return get_expected_type_SPEC_d_i(len);
        case SPEC_U: case SPEC_O: case SPEC_X: case SPEC_X_CAP:
            return get_expected_type_SPEC_u_o_x_X(len);
        case SPEC_F: case SPEC_F_CAP:
        case SPEC_E: case SPEC_E_CAP:
        case SPEC_G: case SPEC_G_CAP:
        case SPEC_A: case SPEC_A_CAP:
            return get_expected_type_SPEC_a_A(len);
        case SPEC_C:
            return (len == LEN_L) ? "wint_t" : "int";
        case SPEC_S:
            return (len == LEN_L) ? "wchar_t *" : "char *";
        case SPEC_P:
            return "void *";
        case SPEC_N:
            return get_expected_type_SPEC_n(len);
        default:
            return "unknown";
    }
}





width ft_check_width(const char **pp) {
    const char *p;
	width result;

	p = *pp;
    result.width_value = -1;
    result.width_position = 0;
    result.flags = 0;
    if (*p == '*')
        ft_handle_asterisk_width(&p, &result);
    else
        ft_handle_numeric_width(&p, &result);
    *pp = p;
    return result;
}

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


void report_invalid_flag(int index) {
    if (index >= 0 && index < 7)
        printf("Invalid flag '%c' for this specifier\n", flag_chars[index]);
}

int valid_flag_combo(unsigned char flags, FormatSpecifier spec)
{
	int bit;

	bit = 0;
    while ( bit < 7)
	{
        if ((flags & (1 << bit)) && compatibility[spec][bit] == 0)
            return bit;
		++bit;
    }
	if (bit >= 0)
	{
	    report_invalid_flag(bit);
		return (0);
	}
    return (1);
}

void ft_handle_asterisk_precision(const char **pp, precision *result) {
    const char *p;
	int pos;
    const char *before;
    int dummy;

	p = *pp;
    result->flags |= HAS_PRECISION | HAS_DYNAMIC_PRECISION;
    p++;
	//fix this
    if (isdigit(*p))
	{
        pos = 0;
        result->precision_position = -1;
        before = p;
        dummy = parse_number_or_positional(&p, &pos);
        if (pos > 0)
		{
            result->precision_position = pos;
            result->flags |= HAS_PRECISION_POSITION;
        }
		else
            p = before;
    }
    *pp = p;
}


void ft_handle_numeric_precision(const char **pp, precision *result) {
    const char *p = *pp;
    int pos = 0;
    int val = parse_number_or_positional(&p, &pos);
    result->arg_position = -1;
    if (val >= 0)
	{
        result->precision_value = val;
        result->flags |= HAS_PRECISION;
    }
    if (pos > 0)
	{
        result->arg_position = pos;
        result->flags |= HAS_POSITIONAL_ARG;
    }
    *pp = p;
}


precision ft_check_precision(const char **pp) {
    const char *p = *pp;
    precision result = {0};

    result.precision_value = -1;
    result.precision_position = 0;
    result.flags = 0;
    if (*p == '.')
	{
        p++;
        if (*p == '*')
            ft_handle_asterisk_precision(&p, &result);
        else
            ft_handle_numeric_precision(&p, &result);
    }
    *pp = p;
    return (result);
}

FormatSpecifier parse_specifier(char c) {
    for (int i = 0; i < 18; i++) {
        if (specifier_str[i][0] == c)
            return (FormatSpecifier)i;
    }
    return SPEC_UNKNOWN;
}




void ft_build_output(Node *node)
{
    const char *append_str = "Parsed OK";

    size_t old_len = node->output ? strlen(node->output) : 0;
    size_t append_len = strlen(append_str);
    char *new_output = malloc(old_len + append_len + 1);
    if (!new_output)
        return;

    if (node->output)
        strcpy(new_output, node->output);
    else
        new_output[0] = '\0';

    strcpy(new_output + old_len, append_str);

    free(node->output);
    node->output = new_output;

    if (node->lout == 0)
        node->lout = old_len + append_len;
}

void analyze_format(Node *node) {
    const char *p = node->text;

    if (!node->valide)
        return;
    if (*p != '%')
        return;
    p++;
    node->flags = parse_flags(&p);
    node->width = ft_check_width(&p);
    node->precision = ft_check_precision(&p);
    node->length = parse_length(&p);
    node->spec = parse_specifier(*p);
    p++;
	if (!valid_flag_combo(node->flags,node->spec))
	{
		node->valide = -2;
		return;
	}
    ft_build_output(node);
}

void ft_handle_percent(Node *node) {
    node->output = malloc(2 * sizeof(char));
    if (!node->output)
        return;
    node->output[0] = '%';
    node->output[1] = '\0';
	node->lout=2;
    node->valide = 0;
}

void append_to_list(List *list, const char *str, int start, int end) {
    Node *new_node;

	new_node = malloc(sizeof(Node));
    if (!new_node)
        return;
	//fix this
    new_node->text = strndup(str + start, end - start);
    if (!new_node->text)
	{
        free(new_node);
        return;
    }
    new_node->output = NULL;
    new_node->valide = 1;
    new_node->next = NULL;
	new_node->lout =0;
    if (list->tail)
        list->tail->next = new_node;
    else
        list->head = new_node;
    list->tail = new_node;
    if ((end - start) == 2 && str[start] == '%' && str[start + 1] == '%')
        ft_handle_percent(new_node);
}

void print_list(const List *list, const char *label) {
    const Node *cur = list->head;
    printf("--- %s ---\n", label);
    int count = 0;

    while (cur) {
        printf("Node %d:\n", ++count);
        printf("  Text:         %s\n", cur->text ? cur->text : "(null)");
        printf("  Format:       %s\n", cur->format ? cur->format : "(null)");
        printf("  Output:       %s\n", cur->output ? cur->output : "(null)");

        // Width Info
        printf("  Width:\n");
        printf("    Arg Position:   %d\n", cur->width.arg_position);
        printf("    Width Position: %d\n", cur->width.width_position);
        printf("    Width Value:    %d\n", cur->width.width_value);
        printf("    Flags:          0x%x\n", cur->width.flags);

        // Precision Info
        printf("  Precision:\n");
        printf("    Arg Position:      %d\n", cur->precision.arg_position);
        printf("    Precision Position:%d\n", cur->precision.precision_position);
        printf("    Precision Value:   %d\n", cur->precision.precision_value);
        printf("    Flags:             0x%x\n", cur->precision.flags);

        // General Flags and specifier
        printf("  Flags:         0x%x\n", cur->flags);
        printf("  Length:        %d\n", cur->length);     // Assuming LengthModifier is an enum
        printf("  Specifier:     %d\n", cur->spec);       // Assuming FormatSpecifier is an enum or int

        printf("-------------------------------\n");

        cur = cur->next;
    }
}

void parse_printf_string(const char *str, List *parts, List *formats) {
    int i = 0, j = 0, b = 0;
    while (str[i]) {
        if (str[i] == '%') {
            if (b != i) append_to_list(parts, str, b, i);
            j = i + 1;
            while (str[j] && !strchr("diouxXfFeEgGaAcspn%", str[j])) j++;
            if (str[j]) {
                append_to_list(formats, str, i, j + 1);
                i = j + 1;
                b = i;
                continue;
            }
        }
        i++;
    }
    if (b < i) append_to_list(parts, str, b, i);
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_POSITIONS 10

int extract_positions(const char *format, int positions[], int max_positions) {
    int count = 0;
    const char *p = format;

    while (*p && count < max_positions) {
        // Look for digit(s) followed by $
        if (isdigit(*p)) {
            const char *start = p;
            int pos = 0;

            // Read the number
            while (isdigit(*p)) {
                pos = pos * 10 + (*p - '0');
                p++;
            }

            // Check for trailing $
            if (*p == '$') {
                positions[count++] = pos;
                p++; // Skip the $
            } else {
                // Rewind if no $
                p = start + 1;
            }
        } else {
            p++;
        }
    }

    return count;  // Return number of positions found
}

int main() {
    // const char *fmt = "This is a test with %d values and %% signs and %%%%%10.2f floats.";
    // List parts, formats;
    // init_list(&parts);
    // init_list(&formats);
    // parse_printf_string(fmt, &parts, &formats);

    // Node *cur = formats.head;

    // while (cur) {
    //     // analyze_format(cur);



    //     cur = cur->next;
    // }

    // print_list(&formats, "Formats");

    const char *fmt = "%4$*2$.*3$Lf";
    int positions[MAX_POSITIONS];
    int num = extract_positions(fmt, positions, MAX_POSITIONS);

    printf("Found %d positional argument(s):\n", num);
    for (int i = 0; i < num; i++) {
        printf("  %d\n", positions[i]);
    }


    return 0;
}
