/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:57:57 by samajat           #+#    #+#             */
/*   Updated: 2022/03/19 17:10:30 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int **allocate_arr(int    argc)
{
    int **pipes;
    int i;

    i = -1;
    pipes = malloc(sizeof(int) * (argc - 2));
    if (!pipes)
        return(0);
    while (++i < argc - 2)
    {
        pipes[i] = malloc(sizeof(int) * (2));
        printf ("size of fd[i] = %lu \n", sizeof(pipes)/sizeof(int));
        if (!pipes[i])
            return(0);
    }
    return (pipes);
}
int first_pipe(int  argc, char **argv, t_data *data, char **env, int    **fd)
{
    data->infile = open (argv[1], O_RDWR, 0777);
    if (data->infile < 0)
    	return (0);
    dup2 (data->infile, STDIN_FILENO);
    dup2 (data->fd[0][1], STDOUT_FILENO);
    close_all (data);
	exec_cmd (data,   argv[2],    env);
    return(1);
}

// int middle_infinite_pipe()
// {

// }

// int last_pipe()
// {

// }

int    generate_pipes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->argc - 2)
    {
	    if (pipe(data->fd[i]) < 0)
		    return (0);
        i++;
    }
    return(1);
}

int main (int argc, char **argv, char **env)
{
	t_data  data;
	int i;
	int	j;

    data.fd = allocate_arr(argc);
    data.last_pipe = argc - 4;
    data.argc = argc;
    data.argv = argv;
    // i = data.fd[3][54];
    printf ("******\n");
    if (!generate_pipes(&data))
        return (0);
	data.id = fork();
	if (!data.id)
        if (!first_pipe(argc, argv, &data, env, data.fd))
            return(0);
    i = 3;
	j = 0;
    while (i < argc - 2)
    {
        data.id = fork();
	    if (!data.id)
	    {
	    	dup2 (data.fd[j][0], 0);
	    	dup2 (data.fd[j + 1][1], 1);
            close_all (&data);
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
    	dup2 (data.fd[data.last_pipe - 1][0], 0);
	    dup2 (data.outfile, 1);
            close_all (&data);
		exec_cmd (&data,   argv[argc - 2],    env);
	}
            close_all (&data);
    return(1);
}