/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:34:51 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 14:37:10 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../includes/pipex.h"
//int execve(const char *path, char *const argv[], char *envp[]);


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

int main(int argc, char **argv, char **env) {
	int id;

	id = fork();
	if (id == 0)
	{
		int	i;
		char *line;
		char **paths;
		char *mypath;
		char **cmd;
		line = extract_paths (env);
		paths = ft_split (line, ':');
		while (paths[i])
		{
			paths[i] = ft_strjoin (paths[i], "/");
			mypath = ft_strjoin (paths[i], argv[1]);
			// cmd = ft_split(argv[1], ' ');
			execve (mypath,argv + 1 , env);
			i++;
		}
	}
	else 
	{
		wait(NULL);
		printf ("The cmd execution is successfull.");
	}
}
