/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:32:50 by hsuner            #+#    #+#             */
/*   Updated: 2023/12/22 15:10:16 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void put_string(char *str, int *len)
{
	if(!str)
		str = "(null)";
	while(*str)
		len += write(1, str++, 1);
}

void put_digit(long long int nbr, int base, int *len)
{
	char *hex = "0123456789abcdef";
	if(nbr < 0)
	{
		nbr *= -1;
		len += write(1, "-", 1);
	}
	if(nbr >= base)
		put_digit((nbr / base), base, len);
	len += write(1, &hex[nbr % base] ,1);
}

int ft_printf(const char *str, ...)
{
	int len;
	va_list ptr;

	len = 0;
	va_start(ptr, str);
	while(*str)
	{
		if(*str == '%')
		{
			str++;
			if((*(str) == 's') || (*(str) == 'd') || (*(str) == 'x'))
			{
				if(*str == 's')
					put_string(va_arg(ptr, char*), &len);
				else if(*str == 'd')
					put_digit((long long int)va_arg(ptr, int), 10, &len);
				else if(*str == 'x')
					put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
			}
			str++;
		}
		else
			len += write(1, str++,1);
	}
	return(va_end(ptr), len);
}
