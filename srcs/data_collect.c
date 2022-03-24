/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_collect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:10:46 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 15:13:32 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fill_data(t_data *data, int argc, char **argv, char **env)
{
	if (!env[0])
		print_error("ERROR : env dosn't exist!\n");
	data->pipes = allocate_arr(argc);
	data->last_pipe = argc - 4;
	data->argc = argc;
	data->argv = argv;
	data->env = env;
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
    free(data->path);
}

void	add_slash_to_paths(t_data *data)
{
	int		i;
	char	*str;

	i = 1;
	while (data->all_paths[++i])
	{
		str = data->all_paths[i];
		data->all_paths[i] = ft_strjoin (str, "/");
		free(str);
	}
}
