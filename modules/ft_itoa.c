
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
	printf("\nrest is '%s' the length is %d \n",str, *len);
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
