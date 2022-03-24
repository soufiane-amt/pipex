/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_collect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:10:46 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 18:20:12 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int get_real_argc(char **argv)
{
    int i;
    int real_argc;

    i = 0;
    real_argc = 0;
    while (argv[i])
    {
        if (ft_memcmp(argv[i], "", 1))
            real_argc++;
        i++;
    }
    return (real_argc);
}

char **get_real_argv(t_data *data, char **argv)
{
    int i;
    int j;
    char    **real_argv;

    i = 0;
    j = 0;
    real_argv = malloc (sizeof(char *) * (data->argc + 1));
    while (argv[i])
    {
        if (ft_memcmp(argv[i], "", 1))
        {
            real_argv[j] = ft_strdup(argv[i]);
            j++;
        }
        i++;
    }
    real_argv[j] = NULL;
    return(real_argv);
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
	int		i;
	char	*str;

	data->path = extract_paths (env);
	if(!data -> path)
		print_error("ERROR : PATH variable dosn't exist!");
	data->all_paths = ft_split (data->path, ':');
    free(data->path);
	i = 1;
	while (data->all_paths[++i])
	{
		str = data->all_paths[i];
		data->all_paths[i] = ft_strjoin (str, "/");
		free(str);
	}
}

void	collect_data(t_data *data, int ac, char **av, char **env, int pipe_included)
{
	if (!env[0])
		print_error("ERROR : env dosn't exist!\n");
	data->argc = get_real_argc(av);
	data->last_pipe = data->argc - 4;
    data->argv = get_real_argv(data, av);
	data->env = env;
    generate_paths(data, data -> env);
    if (pipe_included)
	    data->pipes = allocate_arr(data->argc);
}
