/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alavaud <alavaud@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:59:14 by alavaud      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 17:23:33 by alavaud     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t n;

	n = 0;
	while (s[n])
		++n;
	return (n);
}

void	my_str_append(char *dst, const char *src, size_t src_len)
{
	while (*dst)
	{
		dst++;
	}
	while (src_len--)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
}

char	*str_append(char **base, char *appended, size_t len)
{
	size_t	size;
	size_t	baselen;
	char	*str;

	baselen = 0;
	size = len;
	if (*base)
		baselen = ft_strlen(*base);
	str = (char *)malloc(baselen + size + 1);
	if (str)
	{
		*str = '\0';
		if (*base)
			my_str_append(str, *base, baselen);
		my_str_append(str, appended, len);
	}
	free(*base);
	*base = str;
	return (str);
}
