/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:35:49 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 15:42:20 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->argc - 2)
	{
        printf("close(pipes[%d][0])\n", i);
        printf("close(pipes[%d][1])\n", i);
		close (data->pipes[i][0]);
		close (data->pipes[i][1]);
	}
}

void	exec_cmd(t_data *data, char *command)
{
	int	i;

	i = 0;
	data -> cmd = ft_split (command, ' ');
	while (data->all_paths[i])
	{
		data->mypath = ft_strjoin (data->all_paths[i], data->cmd[0]);
        execve (data->mypath, data->cmd, data->env);
		i++;
	}
}