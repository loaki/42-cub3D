/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:12:29 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/11/29 16:59:02 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strdup(char *src)
{
	int		i;
	char	*ret;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int			ft_substr(char *s, unsigned int start, size_t len)
{
	size_t			j;

	j = 0;
	while (s[start + j] && j < len)
	{
		s[j] = s[start + j];
		j++;
	}
	while (s[j])
	{
		s[j] = 0;
		j++;
	}
	return (1);
}

size_t		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int			ft_strjoin(char **s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = 0;
	while ((*s1)[i])
		i++;
	while (s2[j])
		j++;
	if (!(s = malloc(sizeof(char *) * (1 + i + j))))
		return (0);
	i = -1;
	while ((*s1)[++i])
		s[i] = (*s1)[i];
	j = -1;
	while (s2[++j])
		s[i + j] = s2[j];
	s[i + j] = '\0';
	free(*s1);
	*s1 = s;
	return (1);
}
