/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:54:45 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:54:53 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_internal.h"
#include "pipex.h"

#define STRLEN_PATH 5

static char	**get_paths(char **envp)
{
	char	*all_paths;

	all_paths = *envp++;
	while (all_paths)
	{
		if (!ft_strncmp("PATH=", all_paths, STRLEN_PATH))
			break ;
		all_paths = *envp++;
	}
	if (!all_paths)
		return (NULL);
	return (ft_split(all_paths + STRLEN_PATH, ':'));
}

static char	*find_cmd_on_found(char *to_check)
{
	if (access(to_check, X_OK) == 0)
		return (to_check);
	ft_putstr_fd("pipex: permission denied: ", STDERR_FILENO);
	ft_putendl_fd(to_check, STDERR_FILENO);
	free(to_check);
	return (NULL);
}

static char	*find_cmd(char **paths, char *cmd, char **args)
{
	char	*to_check;
	char	*tmp[3];
	size_t	i;

	tmp[1] = ft_strtok_r(cmd, " \t\n\v\f\r", (const char **)args);
	if (!tmp[1])
		return (NULL);
	tmp[2] = NULL;
	i = (size_t)-1;
	while (paths[++i])
	{
		tmp[0] = paths[i];
		to_check = ft_strjoin_r(tmp, "/");
		if (!to_check)
			return (free(tmp[1]), NULL);
		if (access(to_check, F_OK) == 0)
			return (free(tmp[1]), find_cmd_on_found(to_check));
		free(to_check);
	}
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putendl_fd(tmp[1], STDERR_FILENO);
	free(tmp[1]);
	return (NULL);
}

static int	free_strarr(char **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = (size_t)-1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

int	pipex_sanitize_cmds(t_pipex *pipex, size_t cmd_count)
{
	char	**paths;
	size_t	cmd_idx;
	char	**res;
	int		cmd_not_found;

	cmd_idx = (size_t)-1;
	paths = get_paths(pipex->envp);
	res = ft_calloc(cmd_count + 1, sizeof(char *));
	if (!paths || !res)
		return (free_strarr(paths));
	cmd_not_found = 0;
	while (++cmd_idx < cmd_count)
	{
		res[cmd_idx] = find_cmd(paths, pipex->cmds[cmd_idx],
				pipex->args + cmd_idx);
		if (!res[cmd_idx])
			cmd_not_found = 1;
	}
	free_strarr(paths);
	if (cmd_not_found)
		return (free_strarr(res));
	free(pipex->cmds);
	pipex->cmds = res;
	return (1);
}
