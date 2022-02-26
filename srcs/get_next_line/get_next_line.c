/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:30:08 by samajat           #+#    #+#             */
/*   Updated: 2022/02/26 18:34:34 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	isln(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	fd_is_valid(char *buff, int fd)
{
	if (read (fd, buff, 0) < 0)
	{
		free(buff);
		return (0);
	}
	if (fd < 0 || fd >= 1024)
		return (0);
	return (1);
}

char	*get_new_line(char *str, char *buff, int fd, int *nn)
{
	int		i;
	int		n;
	char	*strf;

	i = 0;
	n = 1;
	if (!str)
		str = ft_strdup("");
	while (n && !isln(str))
	{
		n = read (fd, buff, 2);
		buff[n] = 0;
		strf = str;
		str = ft_strjoin(str, buff);
		free(strf);
	}
	*nn = n;
	free(buff);
	return (str);
}

char	*get_line(char **strr)
{
	char	*strf;
	int		i;
	char	*line;
	char	*str;

	str = *strr;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	strf = str;
	if (isln(str))
	{
		line = ft_substr(str, 0, i + 1);
		str = ft_strdup(str + i + 1);
	}
	else
	{
		line = ft_strdup(str);
		str = NULL;
	}
	*strr = str;
	free (strf);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;
	char		*buff;
	int			n;
	int			i;

	i = 0;
	buff = (char *) malloc (2 + 1);
	if (!fd_is_valid(buff, fd))
		return (0);
	str = get_new_line(str, buff, fd, &n);
	line = get_line(&str);
	if (!n && !line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}