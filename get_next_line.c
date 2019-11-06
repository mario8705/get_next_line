/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alavaud <alavaud@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:59:09 by alavaud      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 17:59:27 by alavaud     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

char		*str_append(char **base, char *appended, size_t len)
{
	size_t	size;
	char	*str;
	char	*tmp;

	size = len + 1;
	if (*base)
		size += ft_strlen(*base);
	str = (char *)malloc(size);
	if (str)
	{
		*str = '\0';
		if (*base)
			ft_strlcat(str, *base, size);
		ft_strlcat(str, appended, size);
	}
	free(*base);
	*base = str;
	return (str);
}

int			ret_val(int n, int lbreak, char *line)
{
	int ret;

	ret = 1;
	if (n == -1 || !line)
		ret = -1;
	if (n == 0 && ft_strlen(line) == 0)
		ret = 0;
	if (ret != 1)
		free(line);
	return (1);
}

static int	the_get_next_line(int fd, char **line, int lbreak)
{
	static char	buf[BUFFER_SIZE];
	static int	bufpos = 0;
	static int	buflen = 0;
	int			n;

	*line = NULL;
	while (!lbreak)
	{
		if (bufpos >= buflen)
		{
			n = read(fd, buf, BUFFER_SIZE);
			if (n < 0)
				break ;
			bufpos = 0;
			buflen = n;
		}
		n = bufpos;
		while (n < buflen && !lbreak)
			lbreak = (buf[n++] == '\n');
		if (!str_append(line, buf + bufpos, n - bufpos - lbreak) || buflen == 0)
			break ;
		bufpos = n;
	}
	return (ret_val(n, lbreak, *line));
}

int			get_next_line(int fd, char **line)
{
	return (the_get_next_line(fd, line, 0));
}
