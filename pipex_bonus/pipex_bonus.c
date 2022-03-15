/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:57:57 by samajat           #+#    #+#             */
/*   Updated: 2022/03/15 15:21:04 by samajat          ###   ########.fr       */
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


void	exec_cmd (t_data *data, char **env)
{
	int	i;

	i = 0;
	while (data->all_paths[i])
	{
		data->all_paths[i] = ft_strjoin (data->all_paths[i], "/");
		data->mypath = ft_strjoin (data->all_paths[i], data->cmd[0]);
		execve (data->mypath, data->cmd , env);
		i++;
	}
}

int main (int argc, char **argv, char **env)
{
	t_data  data;
	int fd[argc - 2][2];
	int i;
	int	l;
    int last_pipe;

    last_pipe = argc - 4;
	l = 0;
	i = -1;
	while (++i < argc - 2)
		if (pipe(fd[i]) < 0)
				return (2);
	data.id = fork();
	if (!data.id)
	{
	    data.infile = open (argv[1], O_RDWR, 0777);
	    if (data.infile < 0)
	    	return (2);
	    dup2 (data.infile, STDIN_FILENO);
	    dup2 (fd[0][1], STDOUT_FILENO);
        close_all (argc - 2 , fd);
		generate_paths(&data, env);
		data.cmd = ft_split (argv[2], ' ');
		exec_cmd (&data, env);
	}
    i = 3;
    while (i < argc - 2)
    {
        data.id = fork();
	    if (!data.id)
	    {
	    	dup2 (fd[l][0], 0);
	    	dup2 (fd[l + 1][1], 1);
            close_all (argc - 2 , fd);
	    	generate_paths(&data, env);
	    	data.cmd = ft_split (argv[i], ' ');
	    	exec_cmd (&data, env);
            return (0);
    	}
        l++;
        i++;
    }
    i = -1;
	data.id = fork();
	if (!data.id)
	{
	    data.outfile = open (argv[argc - 1], O_CREAT | O_RDWR , 0777);
	    if (data.outfile < 0)
	    	return (1);
    	dup2 (fd[last_pipe - 1][0], 0);
	    dup2 (data.outfile, 1);
        close_all (argc - 2 , fd);
		generate_paths(&data, env);
		data.cmd = ft_split (argv[argc - 2], ' ');
		exec_cmd (&data, env);
	}
	wait (NULL);
    close_all (argc - 2, fd);
    close (data.outfile);
    close (data.infile);
}