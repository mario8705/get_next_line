/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alavaud <alavaud@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:59:14 by alavaud      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 18:00:01 by alavaud     ###    #+. /#+    ###.fr     */
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len;

	len = 0;
	while (*dst && len < size)
	{
		dst++;
		len++;
	}
	while (*src)
	{
		if (size > 1 && len < size - 1)
		{
			*dst++ = *src;
			*dst = 0;
		}
		src++;
		len++;
	}
	return (len);
}
