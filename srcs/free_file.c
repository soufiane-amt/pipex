/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:19:45 by samajat           #+#    #+#             */
/*   Updated: 2022/03/23 20:23:08 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void    free_pipe_arr(t_data *data)
{
    int i;

    i = 0;
    while (i < data->argc - 2)
    {
        free(data->pipes[i]);
        i++;
    }
    free(data->pipes);
}

void    free_all_paths(t_data *data)
{
    int i;

    i = 0;
    while (data->all_paths[i])
    {
        free(data->all_paths[i]);
        i++;
    }
    free(data->all_paths);
}
