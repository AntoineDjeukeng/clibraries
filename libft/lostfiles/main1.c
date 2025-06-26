#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

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
    int position[3];
    int mainspecp;
    char *output;
    unsigned char flags;
    LengthModifier length;
    FormatSpecifier spec;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int count;
    int positional;
} List;

void init_list(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->count=0;
    list->positional;
}

unsigned char parse_flags(const char **p)
{
    unsigned char flags = 0;
    int found = 1;

    while (found) {
        found = 0;
        for (int i = 0; i < 7; i++) {
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
Node node = {
    .text = NULL,
    .format = NULL,
    .width = {
        .arg_position = -1,
        .width_position = -1,
        .width_value = -1,
        .flags = 0,
        .type = 0
    },
    .precision = {
        .arg_position = -1,
        .precision_position = -1,
        .precision_value = -1,
        .flags = 0
    },
    .position[0]=-1,
    .position[1]=-1,
    .position[2]=-1,
    .valide = 0,
    .lout = 0,
    .output = NULL,
    .flags = 0,
    .length = 0,     // Assuming enum: NONE
    .spec = 0,       // Assuming enum: NONE or INVALID
    .next = NULL
};

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
int parse_main_arg_position(const char **pp) {
    const char *p = *pp;
    int pos = 0;
    const char *start = p;

    if (!isdigit(*p))
        return 0;

    while (isdigit(*p)) {
        pos = pos * 10 + (*p - '0');
        p++;
    }

    if (*p == '$') {
        p++;
        *pp = p;
        return pos;
    }

    // No positional arg, revert pointer
    *pp = start;
    return 0;
}

void ft_handle_asterisk_width(const char **pp, width *result) {
    const char *p = *pp;
    int pos = 0;
    const char *before = NULL;

    // Mark width as dynamic and present
    // result->flags=0;
    result->flags |= HAS_WIDTH | HAS_DYNAMIC_WIDTH;

    p++; // skip the '*'

    if (isdigit((unsigned char)*p)) {
        before = p;
        (void)parse_number_or_positional(&p, &pos);  // parse positional if exists

        if (pos > 0) {
            result->width_position = pos;
            result->flags |= HAS_WIDTH_POSITION;
        } else {
            // No positional found, reset pointer to before parse attempt
            p = before;
        }
    }

    *pp = p;  // update caller's pointer to after what was parsed
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
    if (pos > 0) {
        result->arg_position = pos;
        result->flags |= HAS_POSITIONAL_ARG;
    }
    *pp = p;
}

uint32_t get_expected_type_SPEC_d_i(LengthModifier len) {
    switch (len) {
        case LEN_HH: return 1u << TYPE_SIGNED_CHAR;
        case LEN_H:  return 1u << TYPE_SHORT;
        case LEN_L:  return 1u << TYPE_LONG;
        case LEN_LL: return 1u << TYPE_LONG_LONG;
        case LEN_J:  return 1u << TYPE_INTMAX_T;
        case LEN_Z:  return 1u << TYPE_SSIZE_T;
        case LEN_T:  return 1u << TYPE_PTRDIFF_T;
        default:     return 1u << TYPE_INT;
    }
}



uint32_t get_expected_type_SPEC_u_o_x_X(LengthModifier len) {
    switch (len) {
        case LEN_HH: return 1u << TYPE_UNSIGNED_CHAR;
        case LEN_H:  return 1u << TYPE_UNSIGNED_SHORT;
        case LEN_L:  return 1u << TYPE_UNSIGNED_LONG;
        case LEN_LL: return 1u << TYPE_UNSIGNED_LONG_LONG;
        case LEN_J:  return 1u << TYPE_UINTMAX_T;
        case LEN_Z:  return 1u << TYPE_SIZE_T;
        case LEN_T:  return 1u << TYPE_PTRDIFF_T;
        default:     return 1u << TYPE_UNSIGNED_INT;
    }
}

uint32_t get_expected_type_SPEC_a_A(LengthModifier len) {
    return (len == LEN_CAPL) ? (1u << TYPE_LONG_DOUBLE) : (1u << TYPE_DOUBLE);
}

uint32_t get_expected_type_SPEC_n(LengthModifier len) {
    switch (len) {
        case LEN_HH: return 1u << TYPE_SIGNED_CHAR_PTR;
        case LEN_H:  return 1u << TYPE_SHORT_PTR;
        case LEN_L:  return 1u << TYPE_LONG_PTR;
        case LEN_LL: return 1u << TYPE_LONG_LONG_PTR;
        case LEN_J:  return 1u << TYPE_INTMAX_T_PTR;
        case LEN_Z:  return 1u << TYPE_SIZE_T_PTR;
        case LEN_T:  return 1u << TYPE_PTRDIFF_T_PTR;
        default:     return 1u << TYPE_INT_PTR;
    }
}


uint32_t get_expected_type(FormatSpecifier spec, LengthModifier len) {
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
            return (len == LEN_L) ? (1u << TYPE_WINT_T) : (1u << TYPE_INT);
        case SPEC_S:
            return (len == LEN_L) ? (1u << TYPE_WCHAR_T_PTR) : (1u << TYPE_CHAR_PTR);
        case SPEC_P:
            return 1u << TYPE_VOID_PTR;
        case SPEC_N:
            return get_expected_type_SPEC_n(len);
        default:
            return 1u << TYPE_UNKNOWN;
    }
}




width ft_check_width(const char **pp) {
    const char *p;
	width result;
    result.arg_position = -1;
    result.width_position = -1;
    result.width_value = -1;
    result.flags = 0;
	p = *pp;
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
Node* create_new_node(void);

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

    int all = parse_main_arg_position(&p);
    node->flags = parse_flags(&p);
    node->width = ft_check_width(&p);
    node->precision = ft_check_precision(&p);
    node->length = parse_length(&p);
    node->spec = parse_specifier(*p);
    p++;
    node->mainspecp= node->position[0];


    if (node->position[0] > 0) {
        node->flags |= HAS_POSITIONAL_ARG;
    }

    if (node->position[1] > 0) {
        node->width.flags |= HAS_DYNAMIC_WIDTH | HAS_WIDTH_POSITION;
        node->width.width_position = node->position[1];
    }

    if (node->position[2] > 0) {
        node->precision.flags |= HAS_DYNAMIC_PRECISION | HAS_PRECISION_POSITION;
        node->precision.precision_position = node->position[2];
    }



	if (!valid_flag_combo(node->flags,node->spec))
	{
		node->valide = -2;
		return;
	}
    ft_build_output(node);
}

#include <stdlib.h>
#include <string.h>

int ft_handle_zero(Node *node)
{
    size_t l = strlen(node->text);
    size_t i;
    if(l>0)
    {
        node->output = realloc(node->output,l);
        if (!node->output)
            return (0);
        i=0;
        while (i<l)
        {
            node->output[node->lout+i]=node->text[i];
            i++;
        }
        
    }
    node->lout+=l;
    node->valide=0;
    return (1);
}

int ft_handle_percent(Node *node) {
    int i;
    int count;
    int j;

    i = 0;
    count = 0;
    j = 0;
    while (node->text[i] == '%')
        i++;
    count = i / 2;
    node->output = malloc(count + 1);
    if (!node->output)
        return (-1);
    j = 0;
    while (j < count)
        node->output[j++] = '%';
    node->output[count] = '\0';
    node->lout = count;
    if (i % 2 != 0)
    {
        node->valide = 1;
        node->text += i - 1;
        return (1);
    }
    node->text += i;
    if (ft_handle_zero(node))
        return (0);
    return (-1);
}



void extract_positions_custom(const char *format, int positions[3]) {
    positions[0] = -1; // main
    positions[1] = -1; // width
    positions[2] = -1; // precision

    const char *p = format;
    while (*p) {
        if (*p == '$') {
            // Find start of number before $
            const char *num_end = p;
            const char *num_start = p - 1;
            while (num_start >= format && isdigit(*num_start)) {
                num_start--;
            }
            num_start++;

            int val = 0;
            for (const char *q = num_start; q < num_end; q++) {
                val = val * 10 + (*q - '0');
            }

            // Check prefix before number_start
            // Look two chars back for '.*'
            if (num_start - 2 >= format && *(num_start - 2) == '.' && *(num_start - 1) == '*') {
                // precision
                positions[2] = val;
            }
            // Look one char back for '*', but NOT preceded by '.'
            else if (num_start - 1 >= format && *(num_start - 1) == '*' &&
                     ! (num_start - 2 >= format && *(num_start - 2) == '.')) {
                // width
                positions[1] = val;
            }
            else {
                // main
                positions[0] = val;
            }
        }
        p++;
    }
}
void append_to_list(List *list, const char *str, int start, int end) {
    Node* new_node = create_new_node();
    int rt;

    if (!new_node)
        return;
    if (list->tail)
        list->tail->next = new_node;
    else
        list->head = new_node;
    list->tail = new_node;
	//fix this
    new_node->text = strndup(str + start, end - start);
    if (!new_node->text)
	{
        free(new_node);
        return;
    }
    rt = ft_handle_percent(new_node);
    if(rt<1)
        return;
    else
        list->count++;
    extract_positions_custom(new_node->text, new_node->position);
    if (new_node->position[0]>0 || new_node->position[1]>0 ||new_node->position[2]>0 )
        list->positional=1;
}

void print_list(const List *list, const char *label) {
    const Node *cur = list->head;
    printf("--- %s ---\n", label);
    int count = 0;

    while (cur) {
        printf("Node %d:  -> main: %d, width: %d, precision: %d\n", ++count,cur->position[0],cur->position[1],cur->position[2]);
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
        printf("  main:     %d\n", cur->mainspecp);       // Assuming FormatSpecifier is an enum or int

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
            while (str[j] && !strchr("diouxXfFeEgGaAcspn", str[j])) j++;
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

Node* create_new_node(void) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("malloc failed");
        return NULL;
    }
    
    // Initialize all fields properly, for example:
    *new_node = (Node){
        .text = NULL,
        .format = NULL,
        .width = {
            .arg_position = -1,
            .width_position = -1,
            .width_value = -1,
            .flags = 0,
            .type = 0
        },
        .precision = {
            .arg_position = -1,
            .precision_position = -1,
            .precision_value = -1,
            .flags = 0
        },
        .valide = 0,
        .lout = 0,
        .output = NULL,
        .flags = 0,
        .length = 0,
        .spec = 0,
        .next = NULL
    };

    return new_node;
}


int extract_positions(const char *format, int positions[3]) {
    positions[0] = -1; // main arg position
    positions[1] = -1; // width arg position
    positions[2] = -1; // precision arg position

    const char *p = format;

    // 1) Extract main argument position (digits followed by $ at start)
    if (isdigit(*p)) {
        int val = 0;
        const char *start = p;
        while (isdigit(*p)) {
            val = val * 10 + (*p - '0');
            p++;
        }
        if (*p == '$') {
            positions[0] = val;
            return 3;  // Found main position, return immediately
        } else {
            p = start;  // rewind if no $
        }
    }

    // 2) Extract width argument position: look for '*' followed by digits + '$'
    while (*p && *p != '.' && positions[1] == -1) {
        if (*p == '*') {
            p++;
            if (isdigit(*p)) {
                int val = 0;
                while (isdigit(*p)) {
                    val = val * 10 + (*p - '0');
                    p++;
                }
                if (*p == '$') {
                    positions[1] = val;
                    return 3;  // Found width position, return immediately
                }
            }
        }
        p++;
    }

    // 3) Extract precision argument position: look for '.' then '*' + digits + '$'
    while (*p && positions[2] == -1) {
        if (*p == '.') {
            p++;
            if (*p == '*') {
                p++;
                if (isdigit(*p)) {
                    int val = 0;
                    while (isdigit(*p)) {
                        val = val * 10 + (*p - '0');
                        p++;
                    }
                    if (*p == '$') {
                        positions[2] = val;
                        return 3;  // Found precision position, return immediately
                    }
                }
            }
        }
        p++;
    }

    return 3;  // return with whatever found or -1s if none
}

#define MAX_POSITIONS 10

int main() {
    const char *fmt =  "%%%%%d %10d %*d %2$*3$d %.5f %.*f %.*3$f %4$*2$.*3$Lf %-+ #0d %lld";
    // const char *fmt =  "%4$*2$.*3$Lf";
    List parts, formats;
    init_list(&parts);
    init_list(&formats);
    parse_printf_string(fmt, &parts, &formats);

    Node *cur = formats.head;
    printf("number of required positional arguement are %d\n",formats.count);
    printf("the positional are set to %d\n", formats.positional);
    while (cur) {
        analyze_format(cur);
        cur = cur->next;
    }

    print_list(&formats, "Formats");
   
    return 0;
}

// #include <stdio.h>
// #include <ctype.h>


// int main() {
//     const char *tests[] = {
//         "%4$*2$.*3$Lf",    // all positional
//         "%*2$d",           // width positional only
//         "%.*3$f",          // precision positional only
//         "%4$d",            // main positional only
//         "%*d",             // width not positional (no $)
//         "%.5f",            // precision not positional (no $)
//         "%d",              // no positional
//         "%*3$d",           // width positional only
//         "%4$.*2$f",        // main and precision positional
//         "%*2$.*3$f",       // width and precision positional
//         "%4$*d",           // main positional, width not positional
//         "%*d.%*d",         // no positional for width or precision
//         "%*3$d.%*2$d",     // width and precision positional
//         "%5$*6$.*7$d",     // all positional
//         "%*2$d.%3$f",      // width positional, main positional only in digits? no, main = 3 (from `%3$f` - no $ means no main positional?), hmm
//         "%4$*d.%.*f",      // main positional only, width & precision no positional
//         "%4$*2$.*Lf",      // main and width positional only
//         "%10d",            // 10 is not positional, should be ignored
//         "%*10d",           // width without positional indicator
//         "%.*10f",          // precision without positional indicator
//         "%*10$d",          // width positional 10
//         "%.*10$f",         // precision positional 10
//     };

//     int positions[3];

//     for (int i = 0; i < (int)(sizeof(tests) / sizeof(tests[0])); i++) {
//         extract_positions_custom(tests[i], positions);
//         printf("Test '%s' -> main: %d, width: %d, precision: %d\n",
//                tests[i], positions[0], positions[1], positions[2]);
//     }

//     return 0;
// }
