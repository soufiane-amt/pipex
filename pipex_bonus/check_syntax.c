/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:46:14 by samajat           #+#    #+#             */
/*   Updated: 2022/03/20 14:17:12 by samajat          ###   ########.fr       */
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

int check_syntax(t_data *data)
{
	int	i;
	int	j;
	int	cmd_found;
	int	result;

	i = 1;
	j = -1;
	result = access(data ->argv[1], F_OK);
	generate_paths(data, data -> env);
	while (data->all_paths[++j])
		data->all_paths[j] = ft_strjoin (data->all_paths[j], "/");
	while (++i < data->argc - 1)
	{
		data -> cmd = ft_split (data -> argv[i], ' ');
		cmd_found = -1;
		j = -1;
		while (data->all_paths[++j] && cmd_found == -1)
		{
			data->mypath = ft_strjoin (data->all_paths[j], data->cmd[0]);
			cmd_found &= access (data->mypath, F_OK);
            free(data->mypath);
		}
		result |= cmd_found;
	}
	return (result);
}