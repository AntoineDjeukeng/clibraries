
#pragma once
#include "libft/libft.h"
#include "src/data_type.h"
#include "tests/tests_utils.h"
#include <math.h>
#include <stdlib.h>
typedef enum { t_false = 0, t_true = 1 } t_bool;

typedef struct s_word
{
	char				c;
	struct s_word		*next;
}						t_word;
typedef struct t_number_type
{
	char				*intpar;
	char				*decpart;
	int					intlen;
	int					declen;
	int					valide;
	int					sign;
}						t_number_type;

