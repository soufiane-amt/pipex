/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesst_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:45:48 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 19:13:42 by samajat          ###   ########.fr       */
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


int main (int argc , char **argv, char **env)
{
    int temp;
    char    *str;
    int     n;
    int id;
    t_data  data;
    int fd[2];


    pipe(fd);
    collect_data(&data, argc, argv, env, 0);
    generate_paths(&data, env);
    str = ft_strdup("");
    temp = open(".temp", O_CREAT | O_RDWR | O_APPEND, 0777);
    while (ft_memcmp(str, "EOF", 3))
    {
        ft_putstr_fd(str, temp);
        str = get_next_line(0);
    }
    id = fork();
    if(!id)
    {
	    data.infile = open (".temp", O_RDONLY, 0777);
	    if (data.infile < 0)
	    	exit (1);
	    dup2 (data.infile, STDIN_FILENO);        
	    dup2 (fd[1], STDOUT_FILENO);
	    close(fd[0]);
	    close(fd[1]);
	    exec_cmd(&data, argv[2]);
    }
    id = fork();
    if(!id)
    {
	    data.outfile = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	    if (data.outfile < 0)
	    	exit (1);
	    dup2 (fd[0], STDIN_FILENO);   
        dup2 (data.outfile, 1); 
	    close(fd[0]);
	    close(fd[1]);
	    exec_cmd(&data, argv[3]);
    }
    waitpid(-1, NULL, 0);
    unlink(".temp");
}