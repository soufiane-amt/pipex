/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:58:30 by samajat           #+#    #+#             */
/*   Updated: 2022/03/23 21:47:21 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


int	child_process(t_data *data, int *fd, char **argv)
{
	data->infile = open (data->argv[1], O_RDWR, 0777);
	if (data->infile < 0)
		return (2);
	dup2 (data->infile, STDIN_FILENO);
	dup2 (fd[1], STDOUT_FILENO);
	close (fd[0]);
	close (fd[1]);
	exec_cmd (data, data->argv[2]);
	return (0);
}

int child_process_t(t_data *data, int *fd, char **argv)
{
    data->outfile = open (data->argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->outfile < 0)
		return (1);
	dup2 (data->outfile, STDOUT_FILENO);
	dup2 (fd[0], STDIN_FILENO);
	close (fd[0]);
	close (fd[1]);
	exec_cmd (data, data->argv[3]);
    return(0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_data	data;
// 	int		fd[2];

// 	data.env = env;
// 	data.argv = argv;
// 	data.argc = argc;
// 	if ((data.argc < 5 || data.argc > 5 || !env[0]) || check_syntax(&data) == -1)
// 		print_error("ERROR!\n");
// 	if (pipe(fd) < 0)
// 		return (2);
// 	data.id = fork();
// 	if (data.id < 0)
// 		return (2);
// 	if (data.id == 0)
// 		child_process (&data, fd, argv);
// 	data.id = fork();
// 	if (data.id < 0)
// 		return (2);
// 	if (data.id == 0)
// 		child_process_t (&data, fd, argv);
//     waitpid(-1, NULL, 0);
// 	return (0);
// }
