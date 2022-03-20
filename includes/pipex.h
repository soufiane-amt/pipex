/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:46:05 by samajat           #+#    #+#             */
/*   Updated: 2022/03/20 20:39:15 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//Headers
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../srcs/get_next_line/get_next_line.h"

//data
typedef struct s_data
{
	int		id;
	int		**pipes;
	char	*path;
	char	**all_paths;
	char	*mypath;
	char	**cmd;
	int		last_pipe;
	int		pipes_nbr;
	int		infile;
	int		outfile;
	char	**argv;
	char	**env;
	int		argc;
}	t_data;

//utils
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	t_free(int	**pipes, int i);
int		generate_pipes(t_data *data);
int		**allocate_arr(int argc);

//main functions
char	*extract_paths(char **env);
void	generate_paths(t_data *data, char **env);
void	exec_cmd(t_data *data, char *command);
void	close_all(t_data *data);
int		check_syntax(t_data *data);
void	fill_data(t_data *data, int argc, char **argv, char **env);

#endif