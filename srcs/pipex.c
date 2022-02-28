/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:58:30 by samajat           #+#    #+#             */
/*   Updated: 2022/02/28 16:01:54 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int main(int argc, char **argv, char **env)
{
	t_data	data;
	int		fd[2];

	if (pipe(fd) < 0)
		return (2);
	data.id = fork();
	if (data.id < 0)
		return (2);
	if (data.id == 0)
	{
		//child process
        data.infile = open (argv[1], O_RDWR, 0777);
        if (data.infile < 0)
            return (2);
        dup2 (data.infile, 0);
		dup2 (fd[1], 1);
        close (fd[0]);
        close (fd[1]);
		data.path = extract_paths (env);
		data.all_paths = ft_split (data.path, ':');
		data.cmd = ft_split (argv[2], ' ');
		exec_cmd (&data, env);
	}
	else 
	{
		//parent process
		wait (NULL);
        data.outfile = open (argv[4], O_CREAT | O_RDWR, 0777);
        if (data.outfile < 0)
            return (1);
        dup2 (data.outfile, 1);
		dup2 (fd[0], 0);
        close (fd[0]);
        close (fd[1]);
		data.path = extract_paths (env);
		data.all_paths = ft_split (data.path, ':');
		data.cmd = ft_split (argv[3], ' ');
		exec_cmd (&data, env);		
	}
	return (0);
}
//