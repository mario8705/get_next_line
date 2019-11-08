/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_bonus.h                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alavaud <alavaud@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 17:25:00 by alavaud      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 18:09:52 by alavaud     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_gnl_context
{
	struct s_gnl_context	*next;
	struct s_gnl_context	*prev;
	int						fd;
	char					buf[BUFFER_SIZE];
	int						bufpos;
	int						buflen;
}				t_gnl_context;

int				get_next_line(int fd, char **line);

char			*str_append(char **base, char *appended, size_t len);
size_t			ft_strlen(const char *s);

#endif
