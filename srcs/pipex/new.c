/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:54:35 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:54:38 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_internal.h"

static t_pipex	*pipex_new_criterr(t_pipex *pipex, char **cmds, char **args)
{
	free(cmds);
	free(args);
	free(pipex);
	return (NULL);
}

t_pipex	*pipex_new(char **envp, int argc, char **argv)
{
	t_pipex	*res;
	size_t	cmd_count;

	res = malloc(sizeof(t_pipex));
	if (!res)
		return (NULL);
	res->envp = envp;
	res->filein = argv[0];
	res->fileout = argv[argc - 1];
	res->cmds = malloc(sizeof(char *) * (size_t)(argc - 1));
	res->args = malloc(sizeof(char *) * (size_t)(argc - 1));
	if (!res->cmds || !res->args)
		return (pipex_new_criterr(res, res->cmds, res->args));
	argc -= 2;
	cmd_count = (size_t)argc;
	res->cmds[argc] = NULL;
	while (--argc >= 0)
		res->cmds[argc] = argv[argc + 1];
	if (!pipex_sanitize_cmds(res, cmd_count))
		return (pipex_new_criterr(res, res->cmds, NULL));
	return (res);
}
