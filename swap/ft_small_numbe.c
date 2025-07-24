/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_numbe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:53:13 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/23 21:13:49 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i = 0;
    char *str;
	int		count = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' )
		{

            if (format[i + 1] == 'c')
            
			{
                char c = (char)va_arg(args, int); // `char` is promoted to `int` in varargs
			write(1, &c, 1);
			count++;
			i += 2;
            }
            if (format[i + 1] == 's') 
			{
				str = va_arg(args, char *);
                int j=0;
                while (str[j])
                {
                    
                    write(1, &str[j++], 1);
                    count++;
                }
                
			i += 2;
            }
		}
		else
		{
			write(1, &format[i], 1);
			count++;
			i++;
		}
	}
	va_end(args);
	return (count);
}



int main(void)
{
    int len = ft_printf("Hello %c%s!\n", 'W',"orld");
    printf("The len is %d\n", len);
    return 0;
}