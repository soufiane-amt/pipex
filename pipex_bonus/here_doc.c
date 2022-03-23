/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:25:07 by samajat           #+#    #+#             */
/*   Updated: 2022/03/23 21:43:57 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    here_doc(t_data *data, int **fd)
{
    int temp;
    char    *str;
    int     n;
    int id;

    n = 1;
    str = ft_strdup("");
    temp = open(".temp", O_CREAT | O_RDWR | O_APPEND, 0777);
    while (ft_memcmp(str, "EOF", 3))
    {
        ft_putstr_fd(str, temp);
        str = get_next_line(0);
    }
    id = fork;
    if(!id)
    {
        if(data->id < 0)
            exit(1);
	    data->infile = open (".temp", O_RDWR, 0777);
	    if (data->infile < 0)
	    	exit (1);
	    dup2 (data->infile, STDIN_FILENO);
	    dup2 (fd[1], STDOUT_FILENO);
	    close_all (data);
	    exec_cmd(data, data -> argv[2]);
    }
    id = fork;
    if(!id)
    {
	    if (data->infile < 0)
	    	exit (1);
	    dup2 (fd[0], STDIN_FILENO);
	    close_all (data);
	    exec_cmd(data, data -> argv[3]);
    }

}