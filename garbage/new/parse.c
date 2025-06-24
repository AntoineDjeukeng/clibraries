#include "ft.h"


void init_list(List *list) {
    list->head = NULL;
    list->tail = NULL;
    list->count=0;
    list->positional;
}
Node* create_new_node(void) {
    Node* new_node;
    
    new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("malloc failed");
        return NULL;
    }
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


int allocate_percent_output(Node *node, int count)
{
    int j;
    
    j = 0;
    node->output = malloc(count + 1);
    if (!node->output)
        return (-1);
    while (j < count) {
        node->output[j] = '%';
        j++;
    }
    node->output[count] = '\0';
    node->lout = count;
    return (0);
}

int ft_handle_percent(Node *node) {
    int i;
    int count;
    
    i = 0;
    while (node->text[i] == '%')
        i++;
    count = i / 2;
    if (allocate_percent_output(node, count) != 0)
        return (-1);
    if (i % 2 != 0) {
        node->valide = 1;
        node->text += i - 1;
        return (1);
    }
    node->text += i;
    if (ft_handle_zero(node))
        return (0);
    return (-1);
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


width parse_width(const char *text) {
    width w = {-1, -1, 0};
    const char *p = text;

    if (*p == '*') {
        p++;
        w.flags |= HAS_WIDTH | HAS_DYNAMIC_WIDTH;
        if (isdigit(*p)) {
            w.flags |= HAS_WIDTH_POSITION;
            w.width_position = 0;
            while (isdigit(*p)) {
                w.width_position = w.width_position * 10 + (*p - '0');
                p++;
            }
            if (*p == '$') p++;
        }
    } else if (isdigit(*p)) {
        w.flags |= HAS_WIDTH;
        w.width_value = 0;
        while (isdigit(*p)) {
            w.width_value = w.width_value * 10 + (*p - '0');
            p++;
        }
    }

    return w;
}


void check_width_case(Node *node) 
{
    // printf("    Flags:             0x%x\n", node->precision.flags);
    width w = parse_width(node->text);
    printf("text %s flags=0x%x, width_value=%d, width_position=%d\n",node->text, w.flags, w.width_value, w.width_position);

    // printf("Text %s:  -> main: %d, width: %d, precision: %d\n",node->text,node->position[0],node->position[1],node->position[2]);
    // if ((node->flags & HAS_WIDTH) == 0) {
    //     // No width at all
    //     printf("No width specified.\n");
    // } else if ((node->flags & HAS_DYNAMIC_WIDTH) == 0) {
    //     // Static width
    //     printf("Static width specified.\n");
    // } else {
    //     // Dynamic width is set
    //     if (node->position[1]== -1) {
    //         // No position given for dynamic width (e.g. %*d)
    //         printf("Dynamic width specified without position.\n");
    //     } else {
    //         // Position given for dynamic width (e.g. %*3$d)
    //         printf("Dynamic width specified with position: %d\n", node->position[1]);
    //     }
    // }
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


unsigned char parse_flags(const char **p) {
    unsigned char flags = 0;

    while (1) {
        switch (**p) {
            case '-': flags |= 0x01; break;  // Left justify
            case '+': flags |= 0x02; break;  // Show sign
            case ' ': flags |= 0x04; break;  // Space before positive number
            case '#': flags |= 0x08; break;  // Alternate form
            case '0': flags |= 0x10; break;  // Zero padding
            default: return flags;           // No more flags found
        }
        (*p)++;  // Move to next character
    }
}

void analyze_format(Node *node) {
    const char *p = node->text;

    if (!node->valide)
        return;
    if (*p != '%')
        return;
    p++;

    if(node->position[0]>-1)
    {
        while (*p != '$')
            p++;
    }
    node->flags = parse_flags(&p);
    // node->width = ft_check_width(&p);
    check_width_case(node);
    
    // node->precision = ft_check_precision(&p);
    // node->length = parse_length(&p);
    // node->spec = parse_specifier(*p);
    // p++;
    // node->mainspecp= node->position[0];


    // if (node->position[0] > 0) {
    //     node->flags |= HAS_POSITIONAL_ARG;
    // }

    // if (node->position[1] > 0) {
    //     node->width.flags |= HAS_DYNAMIC_WIDTH | HAS_WIDTH_POSITION;
    //     node->width.width_position = node->position[1];
    // }

    // if (node->position[2] > 0) {
    //     node->precision.flags |= HAS_DYNAMIC_PRECISION | HAS_PRECISION_POSITION;
    //     node->precision.precision_position = node->position[2];
    // }



	// if (!valid_flag_combo(node->flags,node->spec))
	// {
	// 	node->valide = -2;
	// 	return;
	// }
    // ft_build_output(node);
}



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



/**
 * Extracts positional argument indices from a printf-style format string.
 *
 * This function parses the format string and identifies the position numbers 
 * used for the main value, width (e.g., *), and precision (e.g., .*).
 * The extracted indices are stored in the `positions` array:
 * 
 * positions[0] - main value index
 * positions[1] - width index
 * positions[2] - precision index
 *
 * If a particular index is not found, it remains -1.
 *
 * @param format    The printf-style format string.
 * @param positions An array of 3 integers to store the extracted positions.
 */
void extract_positions_custom(const char *format, int positions[3]) {
    const char *p;
    const char *digit;
    const char *start;
    int val;

    p = format;
    positions[0] = -1;
    positions[1] = -1;
    positions[2] = -1;
    while (*p) {
        if (*p == '$') {
            start = p - 1;
            while (start >= format && isdigit(*start))
                start--;
            start++;
            val = 0;
            digit = start;
            while ( digit < p) {
                val = val * 10 + (*digit - '0');
                digit++;
            }

            if (start - 2 >= format && *(start - 2) == '.' && *(start - 1) == '*') {
                positions[2] = val;
            } else if (*(start - 1) == '*' && !(start - 2 >= format && *(start - 2) == '.')) {
                positions[1] = val;
            } else {
                positions[0] = val;
            }
        }
        p++;
    }
}
