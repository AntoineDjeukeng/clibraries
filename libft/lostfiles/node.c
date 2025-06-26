#include "ft.h"

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
    if (pos > 0) {
        result->arg_position = pos;
        result->flags |= HAS_POSITIONAL_ARG;
    }
    *pp = p;
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

void report_invalid_flag(int index) {
    if (index >= 0 && index < 7)
        printf("Invalid flag '%c' for this specifier\n", flag_chars[index]);
}