/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:37:59 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 15:56:36 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->argc - 2)
	{
        printf("g close(pipes[%d])\n", i);
		if (pipe(data->pipes[i]) < 0)
        {
            free_pipe_arr(data, i);
            free_all_paths(data);
            close_all (data);
			exit (1);
        }
		i++;
	}
	return (1);
}
