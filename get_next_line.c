/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alavaud <alavaud@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:59:09 by alavaud      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 17:49:30 by alavaud     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int			ret_val(int n, int buflen, char **line)
{
	char *linebuf;

	linebuf = *line;
	if (!linebuf || n == -1)
	{
		free(linebuf);
		return (-1);
	}
	if (buflen == 0)
		return (0);
	return (1);
}

static int	the_get_next_line(int fd, char **line, int lbreak)
{
	static char	buf[BUFFER_SIZE];
	static int	bufpos = 0;
	static int	buflen = 0;
	int			n;

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
		if (!str_append(line, buf + bufpos, n - bufpos - lbreak))
			return (-1);
		bufpos = n;
		if (buflen == 0)
			break ;
	}
	return (ret_val(n, buflen, line));
}

int			get_next_line(int fd, char **line)
{
	int ret;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	*line = NULL;
	ret = the_get_next_line(fd, line, 0);
	if (ret == -1)
		*line = NULL;
	return (ret);
}
