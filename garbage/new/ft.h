#pragma once
#pragma once
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

extern const char flag_chars[7];
extern const char *specifier_str[];
extern const char *length_str[];



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



#define HAS_WIDTH             0x01  // bit 0
#define HAS_DYNAMIC_WIDTH     0x02  // bit 1
#define HAS_WIDTH_POSITION    0x08  // bit 3
#define HAS_POSITIONAL_ARG    0x04  // bit 2
#define HAS_PRECISION         0x10  // bit 4
#define HAS_DYNAMIC_PRECISION 0x20  // bit 5
#define HAS_PRECISION_POSITION 0x40 // bit 6

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


void init_list(List *list);
Node* create_new_node(void);
void append_to_list(List *list, const char *str, int start, int end);
void parse_printf_string(const char *str, List *parts, List *formats);
int ft_handle_percent(Node *node);
int allocate_percent_output(Node *node, int count);
int ft_handle_zero(Node *node);
void print_list(const List *list, const char *label);
void extract_positions_custom(const char *format, int positions[3]);
width ft_check_width(const char **pp);
void analyze_format(Node *node);
width ft_check_width(const char **pp);
int parse_number_or_positional(const char **p, int *positional);
void ft_handle_asterisk_width(const char **pp, width *result);
void ft_handle_numeric_width(const char **pp, width *result);
void check_width_case(Node *node);