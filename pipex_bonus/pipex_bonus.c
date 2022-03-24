/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:57:57 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 15:55:22 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


int	first_pipe(t_data *data)
{
    if(data->id < 0)
        exit(1);
	data->infile = open (data -> argv[1], O_RDWR, 0777);
	if (data->infile < 0)
		exit (1);
	dup2 (data->infile, STDIN_FILENO);
	dup2 (data->pipes[0][1], STDOUT_FILENO);
	close_all (data);
	exec_cmd(data, data -> argv[2]);
	return (1);
}

int	middle_infinite_pipe(t_data *data, int *i, int *j)
{
    if(data->id < 0)
        exit(1);
	if (!data->id)
	{
		dup2 (data->pipes[*j][0], 0);
		dup2 (data->pipes[*j + 1][1], 1);
		close_all (data);
		exec_cmd (data, data->argv[*i]);
	}
	(*i)++;
	(*j)++;
	return (0);
}

int	last_pipe(t_data *data)
{
    if(data->id < 0)
        exit(1);
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

	fill_data(&data, argc, argv, env);
	if (data.argc < 5 || check_syntax(&data) == -1)
        print_error("Syntax is not valid!\n");
	if (!generate_pipes(&data))
		return (0);
	data.id = fork();
	if (!data.id)
		if (!first_pipe(&data))
			return (0);    
    i = 3;
	j = 0;
	while (i < argc - 2)
	{
		data.id = fork();
		middle_infinite_pipe(&data, &i, &j);
	}    
	data.id = fork();
	if (!data.id)
		last_pipe(&data);
    waitpid(-1, NULL, 0);
    free_pipe_arr(&data, -1);
    free_all_paths(&data);
    printf("seg is here\n");
    close_all (&data);
    return (1);
}
