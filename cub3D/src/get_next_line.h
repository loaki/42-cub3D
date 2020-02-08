/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:47:51 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/16 18:28:53 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 26
# endif

char			*ft_strdup(char *src);
int				ft_substr(char *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *str);
int				ft_strjoin(char **s1, char *s2);
void			ft_init(char *str);
int				ft_eof(char **line, char **str, char *buffer, int eof);
int				ft_find_nl(char *buffer);
int				ft_nl(char **line, char *str, int nl);
int				get_next_line(int fd, char **line);

#endif
