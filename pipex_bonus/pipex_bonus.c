/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:57:57 by samajat           #+#    #+#             */
/*   Updated: 2022/03/25 15:03:51 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int check_validity(t_data *data)
{
    if (data->is_here_doc && data -> argc >= 6 && check_syntax(data) != -1)
        return (1);
    else if (data->argc >= 5 && check_syntax(data) != -1)
        return (1);
    return (0);
}

int	first_pipe(t_data *data)
{
    char    *infile;
    char    *cmd;

    infile = ft_strdup(data->argv[1]);
    cmd = ft_strdup(data->argv[2]);
    if (data ->is_here_doc)
    {
        infile = ft_strdup(".temp");
        cmd = ft_strdup(data -> argv[3]);
    }
    if(data->id < 0)
        exit(1);
	data->infile = open (infile, O_RDWR, 0777);
	if (data->infile < 0)
		exit (1);
	dup2 (data->infile, STDIN_FILENO);
	dup2 (data->pipes[0][1], STDOUT_FILENO);
	close_all (data);
	exec_cmd(data, cmd);
	return (1);
}

int	middle_infinite_pipe(t_data *data, int  *i)
{
    static int  j = 0;

    if(data->id < 0)
        exit(1);
	if (!data->id)
	{
		dup2 (data->pipes[j][0], 0);
		dup2 (data->pipes[j + 1][1], 1);
		close_all (data);
		exec_cmd (data, data->argv[*i]);
	}
    j++;
	(*i)++;
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

	collect_data(&data, argc, argv, env, 1);
	if (!check_validity(&data))
        print_error("Syntax is not valid!\n");
	if (!generate_pipes(&data))
		return (0);
	data.id = fork();
	if (!data.id)
		if (!first_pipe(&data))
			return (0);    
    i = 3;
	while (i < data.argc - 2)
	{
		data.id = fork();
		middle_infinite_pipe(&data, &i);
	}    
	data.id = fork();
	if (!data.id)
		last_pipe(&data);
    close_all (&data);
    waitpid(-1, NULL, 0);
    free_all_data(&data, 1);
    return (1);
}
