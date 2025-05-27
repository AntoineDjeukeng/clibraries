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

unsigned char parse_flags(const char **p) {
    unsigned char flags = 0;
    int found = 1, i;
    while (found) {
        found = 0;
        for (i = 0; i < 7; i++) {
            if (**p == flag_chars[i]) {
                flags |= (1 << i);
                (*p)++;
                found = 1;
                break;
            }
        }
    }
    return flags;
}

int parse_number_or_positional(const char **p, int *positional) {
    const char *start = *p;
    int val = 0;
    *positional = 0;
    if (!isdigit(**p)) return -1;
    while (isdigit(**p)) {
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    if (**p == '$') {
        *positional = val;
        (*p)++;
        return -1;
    }
    return val;
}

width ft_check_width(const char **pp) {
    const char *p = *pp;
    width result = {0};
    result.width_value = -1;
    result.width_position = 0;
    result.flags = 0;
    if (*p == '*') {
        p++;
        result.flags |= HAS_WIDTH | HAS_DYNAMIC_WIDTH;
        if (isdigit(*p)) {
            int pos = 0;
            int dummy = parse_number_or_positional(&p, &pos);
            if (pos > 0) {
                result.width_position = pos;
                result.flags |= HAS_WIDTH_POSITION;
            }
        }
    } else {
        int pos = 0;
        int val = parse_number_or_positional(&p, &pos);
        if (val >= 0) {
            result.width_value = val;
            result.flags |= HAS_WIDTH;
        }
        if (pos > 0) {
            result.arg_position = pos;
            result.flags |= HAS_POSITIONAL_ARG;
        }
    }
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
precision ft_check_precision(const char **pp) {
    const char *p = *pp;
    precision result = {0};
    result.precision_value = -1;
    result.precision_position = 0;
    result.flags = 0;
    if (*p == '.') {
        p++;
        if (*p == '*') {
            p++;
            result.flags |= HAS_PRECISION | HAS_DYNAMIC_PRECISION;
            if (isdigit(*p)) {
                int pos = 0;
                int dummy = parse_number_or_positional(&p, &pos);
                if (pos > 0) {
                    result.precision_position = pos;
                    result.flags |= HAS_PRECISION_POSITION;
                }
            }
        } else {
            int pos = 0;
            int val = parse_number_or_positional(&p, &pos);
            if (val >= 0) {
                result.precision_value = val;
                result.flags |= HAS_PRECISION;
            }
            if (pos > 0) {
                result.arg_position = pos;
                result.flags |= HAS_POSITIONAL_ARG;
            }
        }
    }
    *pp = p;
    return result;
}

FormatSpecifier parse_specifier(char c) {
    for (int i = 0; i < 18; i++) {
        if (specifier_str[i][0] == c)
            return (FormatSpecifier)i;
    }
    return SPEC_UNKNOWN;
}

LengthModifier parse_length(const char **p) {
    if (strncmp(*p, "hh", 2) == 0) {
        *p += 2; return LEN_HH;
    } else if (strncmp(*p, "ll", 2) == 0) {
        *p += 2; return LEN_LL;
    } else if (**p == 'h') {
        (*p)++; return LEN_H;
    } else if (**p == 'l') {
        (*p)++; return LEN_L;
    } else if (**p == 'L') {
        (*p)++; return LEN_CAPL;
    } else if (**p == 'z') {
        (*p)++; return LEN_Z;
    } else if (**p == 'j') {
        (*p)++; return LEN_J;
    } else if (**p == 't') {
        (*p)++; return LEN_T;
    }
    return LEN_NONE;
}


int ft_check_percent(Node *node, const char **p_ptr) {
    const char *p;
    int i;
    int count;

    p = *p_ptr;
    i = 0;
    count = 0;
    if (*p != '%') 
        return 1;
    while (p[i] == '%' && p[i + 1] == '%') {
        count++;
        i += 2;
    }
    if (count > 0) {
        *p_ptr = p + i;
        node->output = malloc(count + 1);
        if (!node->output)
            return 0;
        i=0;
        while (i < count) {
            node->output[i] = '%';
            i++;
        }
        node->output[count] = '\0';
        node->lout += count;
        return 0;
    }
    return 1;
}

void handle_format_node(Node *node) {
    switch (node->spec) {
        case SPEC_INT:
            if (node->precision.precision_value >= 0) {
                handle_int_with_precision(node);
            } else if (node->width.width_value > 0) {
                handle_int_with_width(node);
            } else {
                handle_plain_int(node);
            }
            break;

        case SPEC_STRING:
            if (node->precision.precision_value >= 0) {
                handle_string_with_precision(node);
            } else {
                handle_plain_string(node);
            }
            break;

        case SPEC_FLOAT:
            if (node->flags & FLAG_ZERO) {
                handle_zero_padded_float(node);
            } else {
                handle_plain_float(node);
            }
            break;

        default:
            handle_unknown_specifier(node);
            break;
    }
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

    if (!ft_check_percent(node, &p))
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
    ft_build_output(node);
}

void append_to_list(List *list, const char *str, int start, int end) {
    Node *new_node = malloc(sizeof(Node));
    if(!new_node)
        return;
    
    new_node->text = strndup(str + start, end - start);
    new_node->output = NULL;
    new_node->next = NULL;
    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
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

int main() {
    const char *fmt = "This is a test with %d values and %% signs and %%%%%10.2f floats.";
    List parts, formats;
    init_list(&parts);
    init_list(&formats);
    parse_printf_string(fmt, &parts, &formats);

    Node *cur = formats.head;
    while (cur) {
        analyze_format(cur);
        cur = cur->next;
    }

    print_list(&formats, "Formats");
    return 0;
}
