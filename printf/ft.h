#pragma once

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

#define HAS_WIDTH          0x01
#define HAS_DYNAMIC_WIDTH  0x02
#define HAS_POSITIONAL_ARG 0x04
#define HAS_WIDTH_POSITION 0x08
#define HAS_PRECISION          0x01
#define HAS_DYNAMIC_PRECISION  0x02
#define HAS_PRECISION_POSITION 0x08


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
extern int compatibility[18][7];
extern const char *length_str[];
extern const char *specifier_str[];
extern const char flag_chars[7];

width ft_check_width(const char **pp);

int parse_number_or_positional(const char **p, int *positional);
unsigned char parse_flags(const char **p);
void init_list(List *list);
unsigned char parse_flags(const char **p);
void init_list(List *list);
width ft_check_width(const char **pp);
void ft_handle_numeric_width(const char **pp, width *result);
void report_invalid_flag(int index);
void ft_handle_asterisk_width(const char **pp, width *result);