/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:39:11 by samajat           #+#    #+#             */
/*   Updated: 2022/03/17 22:30:51 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_str(char *limit)
{
	char *text;
	char *str;
	int		n;

	str = ft_strdup("");
	text = ft_strdup("");
	n = 1;
	while (ft_memcmp(limit, str, ft_strlen(str) - 1))
	{
		text = ft_strjoin(text, str);
		str = get_next_line(0);
	}
	return (text);
}

int	is_herdoc (char **argv)
{
	if (ft_memcmp(argv[1], "here_doc", ft_strlen("here_doc")))
		return (1);
	return (0);
}

int	child_process (t_data *data, char **argv, char **env, int *fd)
{
	dup2 (fd[1], STDOUT_FILENO);
    get_str(argv[2]);
	// ft_putstr_fd(get_str(argv[2]), fd[1]);
	close (fd[0]);
	close (fd[1]);
	generate_paths(data, env);
	data->cmd = ft_split (argv[3], ' ');
	exec_cmd (data, env);
	return (0);
}


int    main (int argc, char **argv, char **env)
{
    t_data	data;
	int		fd[2];
	char *str;

	if (pipe(fd) < 0)
		return (2);
	data.id = fork();
	if (data.id < 0)
		return (2);
	if (data.id == 0)
		child_process (&data, argv, env, fd);
	wait (NULL);
    data.id = fork();
	if (data.id == 0)
    {
	    str = ft_strdup("");
	    while (str)
    	{
	    	str = get_next_line(fd[0]);
	    	printf("%s", str);
	    }
        close(fd[0]);
        close(fd[1]);
        exit(1);
    }
	// data.outfile = open (argv[argc - 1], O_CREAT | O_RDWR, 0777);
	// if (data.outfile < 0)
	// 	return (1);
	// dup2 (data.outfile, STDOUT_FILENO);
	// dup2 (fd[0], STDIN_FILENO);
	// close (fd[0]);
	// close (fd[1]);
	// generate_paths(&data, env);
	// data.cmd = ft_split (argv[4], ' ');
	// exec_cmd (&data, env);
	return (0);
}