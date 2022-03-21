/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:57:57 by samajat           #+#    #+#             */
/*   Updated: 2022/03/21 19:59:47 by samajat          ###   ########.fr       */
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

int	first_pipe(t_data *data)
{
    // ft_putstr_fd(2, "ok\n");
	data->infile = open (data -> argv[1], O_RDWR, 0777);
	if (data->infile < 0)
		return (0);
	dup2 (data->infile, STDIN_FILENO);
	dup2 (data->pipes[0][1], STDOUT_FILENO);
	close_all (data);
	exec_cmd(data, data -> argv[2]);
	return (1);
}

int	middle_infinite_pipe(t_data *data, int *i, int *j)
{
	if (!data->id)
	{
        // while (1);
		dup2 (data->pipes[*j][0], 0);
		dup2 (data->pipes[*j + 1][1], 1);
		close_all (data);
		exec_cmd (data, data->argv[*i]);
	}
    waitpid(data->id, NULL, 0);
	(*i)++;
	(*j)++;
	return (0);
}

int	last_pipe(t_data *data)
{
	data->outfile = open (data->argv[data->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->outfile < 0)
		return (1);
	dup2 (data->pipes[data->last_pipe - 1][0], 0);
	dup2 (data->outfile, 1);
	close_all (data);
	exec_cmd (data, data->argv[data->argc - 2]);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	int		j;

    // printf("hello");
	fill_data(&data, argc, argv, env);
	if (data.argc < 5 || check_syntax(&data) == -1)
        print_error("Syntax is not valid!\n");
	if (!generate_pipes(&data))
		return (0);
	data.id = fork();
	if (!data.id)
		if (!first_pipe(&data))
			return (0);
    wait(NULL);
	i = 3;
	j = 0;
	while (i < argc - 2)
	{
		data.id = fork();
		middle_infinite_pipe(&data, &i, &j);
	}
    // waitpid(-1, NULL, 0);
    // wait(NULL);
    // if(!data.id)
    // {
    //     wait(NULL);
    //     wait(NULL);
    //     wait(NULL);
    // }
	data.id = fork();
	if (!data.id)
		last_pipe(&data);
    // waitpid(-1, NULL, 0);
	close_all (&data);
    return (1);
}
