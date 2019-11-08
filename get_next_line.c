/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alavaud <alavaud@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:59:09 by alavaud      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 17:22:40 by alavaud     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int			ret_val(int n, char *line)
{
	int ret;

	ret = 1;
	if (n == -1 || !line)
		ret = -1;
	if (n == 0 && ft_strlen(line) == 0)
		ret = 0;
	if (ret != 1)
		free(line);
	return (ret);
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
	return (ret_val(n, *line));
}

int			get_next_line(int fd, char **line)
{
	if (BUFFER_SIZE <= 0)
		return (-1);
	return (the_get_next_line(fd, line, 0));
}
