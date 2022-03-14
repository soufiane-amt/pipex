/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:48:56 by samajat           #+#    #+#             */
/*   Updated: 2022/03/03 14:54:08 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

#define PROCESS_NUM 3

void close_all_files (int	**fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(fd[i][0]);
		close (fd[i][1]);
	}
}

static char *extract_paths (char **env)
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
	// int PROCESS_NUM = argc ;
	int fd[PROCESS_NUM - 1][2];
	int	ids[PROCESS_NUM - 1];
	int i;
	int	j;
	int	l;
	int infile;
	char *line;
	char **paths;
	char *mypath;
	char **cmd;
	char *str;

	i = 0;
	while (i < PROCESS_NUM)
	{
		if (pipe(fd[i]) < 0)
			return (-1);
		i++;
	}
	i = 0;
    ids[i] = fork();
    if (ids[i] < 0)
        return (1);
    if (ids[i] == 0)
    {
        dup2(fd[0][1], 1);
        line = extract_paths (env);
		paths = ft_split (line, ':');
		cmd = ft_split (argv[i + 2], ' ');
		l = 0;
		while (paths[l])
		{	
			paths[l] = ft_strjoin (paths[l], "/");
			mypath = ft_strjoin (paths[l], cmd[0]);
			execve (mypath, cmd , env);
			l++;
		}
        return (0);
    }
    // i++;
	// while (i < PROCESS_NUM)
	// {
	// 	ids[i] = fork();
	// 	if (ids[i] < 0)
	// 		return (-1);
	// 	if (!ids[i])
	// 	{

	// 		line = extract_paths (env);
	// 		paths = ft_split (line, ':');
	// 		cmd = ft_split (argv[i + 2], ' ');
	// 		l = 0;
	// 		while (paths[l])
	// 		{	
	// 			paths[l] = ft_strjoin (paths[l], "/");
	// 			mypath = ft_strjoin (paths[l], cmd[0]);
	// 			execve (mypath, cmd , env);
	// 			l++;
	// 		}
	// 		return (0);
	// 	}
	// 	i++;
	// }
    wait (NULL);
    read (fd[0][0], str, 20);
    close_all_files(fd, 2);
	return (0);
}