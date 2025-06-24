
#include "libft.h"

static int	count_digits(int n)
{
	int	len;
	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}


char *ft_itoa_len(int n, int *len)
{
	char	*str;
	long	num;
	int 	lent;

	lent = count_digits(n);
	*len = lent;
	str = malloc(lent + 1);
	num = n;
	if (!str)
		return (NULL);
	str[lent] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		if(!(int)(-num) && (int)(-num -1))
			num++;
		num = -num;
	}
	else if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--lent] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}


void split_float(float n, int precision, long *int_part, long *dec_part)
{
    float frac_part;
    long power;
    int i;

    *int_part = (long)n;
    frac_part = n - (float)(*int_part);
    if (frac_part < 0) frac_part = -frac_part;
    power = 1;
    i = 0;
    while (i < precision) {
        power *= 10;
        i++;
    }
    *dec_part = (long)(frac_part * power + 0.5f);
}

void print_float(float n, int precision) {
    long int_part, dec_part;
    split_float(n, precision, &int_part, &dec_part);


    int len_int, len_dec;
    char *str_int = ft_itoa_len(int_part, &len_int);
    char *str_dec = ft_itoa_len(dec_part, &len_dec);
	

    // Handle negative float with 0 integer part
    if (n >-1 && n <0)
        write(1, "-", 1);

    write(1, str_int, len_int);
    write(1, ".", 1);

	str_dec = ft_pad_string(str_dec, precision, '0',false);
    write(1, str_dec, precision);
    write(1, "\n", 1);

    free(str_int);
    free(str_dec);
}

char *ft_ftoa_len(int n, int *len)
{
	char	*str;
	long	num;
	int 	lent;


	lent = count_digits(n);
	*len = lent;
	str = malloc(lent + 1);
	num = n;
	if (!str)
		return (NULL);
	str[lent] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		if(!(int)(-num) && (int)(-num -1))
			num++;
		num = -num;
	}
	else if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--lent] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}




//n and m are int an priority on m
//printf("%n.md" 42);
// char *ft_print_di(int n,int m, int numb)
// {
// 	int lenght;
// 	char *str;

// 	str =ft_itoa_len(numb,&lenght);
// 	str = ft_right_align(str,m,'0');
// 	if (n>m)
// 		str = ft_right_align(str,n,' ');
// 	return str;
// }




// int main()
// {
// 	char *str;
// 	int n;

// 	str=ft_print_di(8,5,54);
// 	printf("'%s'\n", str);
// 	free(str);

// 	return 0;
// }
