/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:35:49 by samajat           #+#    #+#             */
/*   Updated: 2022/03/21 17:40:58 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->argc - 2)
	{
		close (data->pipes[i][0]);
		close (data->pipes[i][1]);
	}
}

char	*extract_paths(char **env)
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

void	generate_paths(t_data *data, char **env)
{
	data->path = extract_paths (env);
	if(!data -> path)
		print_error("ERROR : PATH variable dosn't exist!");
	data->all_paths = ft_split (data->path, ':');
}

void	exec_cmd(t_data *data, char *command)
{
	int	i;

	i = 0;
	data -> cmd = ft_split (command, ' ');
	while (data->all_paths[i])
	{
		data->mypath = ft_strjoin (data->all_paths[i], data->cmd[0]);
        execve (data->mypath, data->cmd, data->env);
		i++;
	}
}
