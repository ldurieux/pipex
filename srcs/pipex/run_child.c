/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:54:40 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:54:42 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_internal.h"

#define ERROR	127
#define SUCCESS	0

static void	run_child_exit(char **str_arr, int ret_code)
{
	size_t	i;

	if (!str_arr)
		exit(ret_code);
	i = (size_t)-1;
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr);
	exit(ret_code);
}

void	pipex_run_child(char **envp, char *cmd, char *args, int fds[2])
{
	char	**res_args;
	char	**cmd_args;
	size_t	size;

	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	cmd_args = ft_split(args, ' ');
	if (!cmd_args)
		run_child_exit(NULL, ERROR);
	size = (size_t)-1;
	while (cmd_args[++size])
		;
	res_args = malloc(sizeof(char *) * (size + 2));
	if (!res_args)
		run_child_exit(cmd_args, ERROR);
	res_args[0] = cmd;
	ft_memcpy((void *)(res_args + 1), (void *)cmd_args,
		sizeof(char *) * (size + 1));
	free(cmd_args);
	if (execve(cmd, res_args, envp) != -1)
		run_child_exit(res_args, SUCCESS);
	run_child_exit(res_args, ERROR);
}
