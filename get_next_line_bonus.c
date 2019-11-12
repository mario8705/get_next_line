/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alavaud <alavaud@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 17:28:52 by alavaud      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 18:15:37 by alavaud     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_context	*ctx_retrieve(t_gnl_context **lhead, int fd)
{
	t_gnl_context *entry;

	entry = *lhead;
	while (entry)
	{
		if (entry->fd == fd)
			return (entry);
		entry = entry->next;
	}
	entry = (t_gnl_context *)malloc(sizeof(t_gnl_context));
	if (entry)
	{
		entry->next = *lhead;
		entry->fd = fd;
		entry->bufpos = 0;
		entry->buflen = 0;
		*lhead = entry;
	}
	return (entry);
}

void			ctx_finish(t_gnl_context **lhead, t_gnl_context *ctx)
{
	t_gnl_context *prev;
	t_gnl_context *entry;

	prev = NULL;
	entry = *lhead;
	while (entry)
	{
		if (entry == ctx)
		{
			if (prev)
				prev->next = entry->next;
			if (entry == *lhead)
				*lhead = entry->next;
			break ;
		}
		prev = entry;
		entry = entry->next;
	}
	free(ctx);
}

int				ctx_refill_buffer(t_gnl_context *context)
{
	int n;

	n = 1;
	if (context->bufpos >= context->buflen)
	{
		n = read(context->fd, context->buf, BUFFER_SIZE);
		context->bufpos = 0;
		context->buflen = n;
	}
	return (n);
}

int				gnl_core(t_gnl_context *context, char **line)
{
	int lbreak;
	int n;
	int s;

	lbreak = 0;
	*line = NULL;
	while (!lbreak)
	{
		if ((n = ctx_refill_buffer(context)) < 0)
			break ;
		s = context->bufpos;
		while (s < context->buflen && !lbreak)
			lbreak = (context->buf[s++] == '\n');
		if (!str_append(line, context->buf + context->bufpos,
			s - context->bufpos - lbreak) || n == 0)
			break ;
		context->bufpos = s;
	}
	if (n == -1 || !(*line))
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	return (n == 0 ? 0 : 1);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl_context	*lhead = NULL;
	t_gnl_context			*ctx;
	int						n;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line ||
		!(ctx = ctx_retrieve(&lhead, fd)))
		return (-1);
	n = gnl_core(ctx, line);
	if (n <= 0)
		ctx_finish(&lhead, ctx);
	if (n != 1)
		free(*line);
	return (n);
}
