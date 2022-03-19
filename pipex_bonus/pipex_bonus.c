/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:57:57 by samajat           #+#    #+#             */
/*   Updated: 2022/03/19 15:44:42 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int    generate_pipes(int argc, int fd[argc - 2][2])
{
    int i;

    i = -1;
    while (++i < argc - 2)
	    if (pipe(fd[i]) < 0)
		    return (0);
    return(1);
}

void	exec_cmd (t_data *data, char *command, char **env)
{
	int	i;

	i = 0;
	generate_paths(data, env);
	data -> cmd = ft_split (command, ' ');
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
	int	j;

    data.last_pipe = argc - 4;
    if (!generate_pipes(argc, fd))
        return (1);
	data.id = fork();
	if (!data.id)
	{
	    data.infile = open (argv[1], O_RDWR, 0777);
	    if (data.infile < 0)
	    	return (1);
	    dup2 (data.infile, STDIN_FILENO);
	    dup2 (fd[0][1], STDOUT_FILENO);
        close_all (argc - 2 , fd);
		exec_cmd (&data,   argv[2],    env);
	}
    i = 3;
	j = 0;
    while (i < argc - 2)
    {
        data.id = fork();
	    if (!data.id)
	    {
	    	dup2 (fd[j][0], 0);
	    	dup2 (fd[j + 1][1], 1);
            close_all (argc - 2 , fd);
		    exec_cmd (&data,   argv[i],    env);
            return (0);
    	}
        j++;
        i++;
    }
	data.id = fork();
	if (!data.id)
	{
	    data.outfile = open (argv[argc - 1], O_CREAT | O_RDWR , 0777);
	    if (data.outfile < 0)
	    	return (1);
    	dup2 (fd[data.last_pipe - 1][0], 0);
	    dup2 (data.outfile, 1);
        close_all (argc - 2 , fd);
		exec_cmd (&data,   argv[argc - 2],    env);
	}
    close_all(argc - 2, fd);
}