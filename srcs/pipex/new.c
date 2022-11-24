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

#define LEN_HERE_DOC 8

static t_pipex	*pipex_new_criterr(t_pipex *pipex, char **cmds, char **args)
{
	free(cmds);
	free(args);
	if (pipex)
		free(pipex->here_doc);
	free(pipex);
	return (NULL);
}

static t_pipex	*pipex_new_here_doc(t_pipex *res, int argc, char **argv)
{
	size_t	cmd_count;

	res->here_doc = ft_strdup(argv[1]);
	res->cmds = malloc(sizeof(char *) * (size_t)(argc - 1));
	res->args = malloc(sizeof(char *) * (size_t)(argc - 1));
	if (!res->cmds || !res->args)
		return (pipex_new_criterr(res, res->cmds, res->args));
	res->filein = 0;
	argc -= 3;
	cmd_count = (size_t)argc;
	res->cmds[argc] = NULL;
	while (--argc >= 0)
		res->cmds[argc] = argv[argc + 2];
	if (!pipex_sanitize_cmds(res, cmd_count))
		return (pipex_new_criterr(res, res->cmds, NULL));
	return (res);
}

t_pipex	*pipex_new(char **envp, int argc, char **argv)
{
	t_pipex	*res;
	size_t	cmd_count;

	res = malloc(sizeof(t_pipex));
	if (!res)
		return (NULL);
	res->envp = envp;
	res->here_doc = NULL;
	res->fileout = argv[argc - 1];
	if (ft_strncmp("here_doc", argv[0], LEN_HERE_DOC) == 0)
		return (pipex_new_here_doc(res, argc, argv));
	res->cmds = malloc(sizeof(char *) * (size_t)(argc - 1));
	res->args = malloc(sizeof(char *) * (size_t)(argc - 1));
	if (!res->cmds || !res->args)
		return (pipex_new_criterr(res, res->cmds, res->args));
	res->filein = argv[0];
	argc -= 2;
	cmd_count = (size_t)argc;
	res->cmds[argc] = NULL;
	while (--argc >= 0)
		res->cmds[argc] = argv[argc + 1];
	if (!pipex_sanitize_cmds(res, cmd_count))
		return (pipex_new_criterr(res, res->cmds, NULL));
	return (res);
}
