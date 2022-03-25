/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:19:45 by samajat           #+#    #+#             */
/*   Updated: 2022/03/25 15:25:42 by samajat          ###   ########.fr       */
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

void	free_pipe_arr(t_data *data, int j)
{
	int	i;

	i = 0;
	if (j == -1)
		j = data->argc - 2;
	while (i < j)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
}

void	free_all_paths(t_data *data)
{
	int	i;

	i = 0;
	while (data->all_paths[i])
	{
		free(data->all_paths[i]);
		i++;
	}
	free(data->all_paths);
}

void	free_all_data(t_data *data, int pipe_arr_included)
{
	free_all_paths(data);
	free_arr(data->argv);
	if (pipe_arr_included)
		free_pipe_arr(data, -1);
	if (data -> is_here_doc)
		unlink(".temp");
}
