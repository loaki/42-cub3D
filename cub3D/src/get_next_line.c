/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:25:36 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/11/29 17:59:49 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_init(char *str)
{
	int i;

	i = 0;
	while (i <= BUFFER_SIZE)
	{
		str[i] = 0;
		i++;
	}
}

int		ft_eof(char **line, char **str, char *buffer, int eof)
{
	if (ft_find_nl(buffer) != -1 && eof != 0)
	{
		if (!(ft_strjoin(str, buffer)))
			return (-1);
		*line = ft_strdup(*str);
		if (!(ft_substr(*line, 0, ft_find_nl(*str))))
			return (-1);
		if (!(ft_substr(*str, ft_find_nl(*str) + 1, ft_strlen(*str))))
			return (-1);
		return (1);
	}
	else if (eof != 0 || ft_strlen(*str) != 0)
	{
		if (!(ft_substr(buffer, 0, eof)) || (!(ft_strjoin(str, buffer))))
			return (-1);
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return (0);
	}
	*line = ft_strdup("");
	free(*str);
	*str = NULL;
	return (0);
}

int		ft_find_nl(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ft_nl(char **line, char *str, int nl)
{
	*line = ft_strdup(str);
	if (!(ft_substr(*line, 0, nl)))
		return (-1);
	if (!(ft_substr(str, nl + 1, ft_strlen(str))))
		return (-1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int				nl;
	int				eof;
	char			buffer[BUFFER_SIZE + 1];
	static char		*str[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || !line || (eof = (read(fd, 0, 0))) == -1)
		return (-1);
	ft_init(buffer);
	if (str[fd] == NULL)
	{
		if (!(str[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		ft_init(str[fd]);
	}
	while (((nl = ft_find_nl(str[fd])) == -1) &&
		((eof = read(fd, buffer, BUFFER_SIZE)) == BUFFER_SIZE))
	{
		if (!(ft_strjoin(&(str[fd]), buffer)))
			return (-1);
		ft_init(buffer);
	}
	if (nl >= 0)
		return (ft_nl(line, str[fd], nl));
	return (ft_eof(line, &(str[fd]), buffer, eof));
}
