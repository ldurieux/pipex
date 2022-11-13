#include "pipex.h"

static char	**get_paths(char **envp)
{
	char	*all_paths;

	all_paths = *envp++;
	while (all_paths)
	{
		if (!ft_strncmp("PATH=", all_paths, 5))
			break ;
		all_paths = *envp++;
	}
	if (!all_paths)
		return (NULL);
	return (ft_split(all_paths + 5, ':'));
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
		{
			free(tmp[1]);
			return (NULL);
		}
		if (access(to_check, F_OK) == 0)
		{
			free(tmp[1]);
			if (access(to_check, X_OK) == 0)
				return (to_check);
			ft_putstr_fd("pipex: permission denied: ", STDERR_FILENO);
			ft_putendl_fd(cmd, STDERR_FILENO);
			free(to_check);
			return (NULL);
		}
		free(to_check);
	}
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putendl_fd(tmp[1], STDERR_FILENO);
	free(tmp[1]);
	return (NULL);
}

static void	free_strarr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = (size_t)-1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static int	sanitize_cmds(t_pipex *pipex, size_t cmd_count)
{
	char	**paths;
	size_t	cmd_idx;
	char	**res;
	int		found_res;

	paths = get_paths(pipex->envp);
	if (!paths)
		return (0);
	cmd_idx = (size_t)-1;
	res = ft_calloc(cmd_count + 1, sizeof(char *));
	if (!res)
	{
		free_strarr(paths);
		return (0);
	}
	found_res = 1;
	while (++cmd_idx < cmd_count)
	{
		res[cmd_idx] = find_cmd(paths, pipex->cmds[cmd_idx],
								pipex->args + cmd_idx);
		if (!res[cmd_idx])
			found_res = 0;
	}
	free_strarr(paths);
	if (!found_res)
	{
		free_strarr(res);
		return (0);
	}
	free(pipex->cmds);
	pipex->cmds = res;
	return (1);
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
	{
		free(res->cmds);
		free(res->args);
		free(res);
		return (NULL);
	}
	argc -= 2;
	cmd_count = (size_t)argc;
	res->cmds[argc] = NULL;
	while (--argc >= 0)
		res->cmds[argc] = argv[argc + 1];
	if (!sanitize_cmds(res, cmd_count))
	{
		free(res->cmds);
		free(res);
		return (NULL);
	}
	return (res);
}
