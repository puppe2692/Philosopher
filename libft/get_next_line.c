/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibenoit <nibenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:47:47 by nibenoit          #+#    #+#             */
/*   Updated: 2023/01/16 11:12:02 by nibenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gnl_read(int fd, char *buf, char **str)
{
	int		i;
	char	*tmp;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		while (i > 0)
		{
			buf[i] = 0;
			if (!*str)
				*str = ft_substr(buf, 0, i);
			else
			{
				tmp = *str;
				*str = ft_strjoin(*str, buf);
				free(tmp);
			}
			if (ft_strchr(buf, '\n'))
				break ;
			i = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
}

static char	*gnl_process(char **str)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;

	if (!*str)
		return (0);
	if (!ft_strchr(*str, '\n'))
	{
		ret = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = 0;
		return (ret);
	}
	i = ft_strlen(*str);
	j = ft_strlen(ft_strchr(*str, '\n'));
	ret = ft_substr(*str, 0, i - j + 1);
	tmp = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, j - 1);
	free(tmp);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, buf, 0) == -1)
	{
		free(buf);
		return (0);
	}
	gnl_read(fd, buf, &str);
	return (gnl_process(&str));
}
