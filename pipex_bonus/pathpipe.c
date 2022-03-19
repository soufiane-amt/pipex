/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path&pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:35:49 by samajat           #+#    #+#             */
/*   Updated: 2022/03/19 14:36:11 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void close_all (int a, int fd[a][2])
{
    int i;

    i = -1;
    while (++i < a)
    {
        close (fd[i][0]);
        close (fd[i][1]);
    }
}

char *extract_paths (char **env)
{
	int		i;
	char	*line;
	int		path_length;

	i = 0;
	while (env[i])
	{
		line = ft_substr (env[i], 0, 4);
		path_length = ft_strlen (env[i]);
		if (!ft_memcmp (line, "PATH", 4))
		{
			free (line);
			return (ft_substr(env[i], 5, path_length));
		}
		free (line);
		i++;
	}
	return (NULL);
}

void generate_paths(t_data *data, char **env)
{
	data->path = extract_paths (env);
	data->all_paths = ft_split (data->path, ':');
}
