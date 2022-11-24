/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:54:38 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:54:40 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_internal.h"

#define IN 0
#define OUT 1

static int	cmd_fork(char **envp, char *cmd, char *args, int fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		pipex_run_child(envp, cmd, args, fds);
	else if (pid > 0)
		return (pipex_run_parent(pid, fds[1]) == 0);
	else
		ft_putendl_fd("fork error\n", STDERR_FILENO);
	return (0);
}

static int	run_first(t_pipex *pipex, int fd_in, int fd_out)
{
	int	fds[2];
	int	res;

	fds[IN] = fd_in;
	fds[OUT] = fd_out;
	res = cmd_fork(pipex->envp, pipex->cmds[0], pipex->args[0], fds);
	close(fd_in);
	return (res);
}

static int	run_last(t_pipex *pipex, int fd_in, int fd_out, size_t cmd_idx)
{
	int	fds[2];
	int	res;

	fds[IN] = fd_in;
	fds[OUT] = fd_out;
	res = cmd_fork(pipex->envp, pipex->cmds[cmd_idx], pipex->args[cmd_idx],
			fds);
	close(fd_in);
	close(fd_out);
	return (res);
}

static int	run_cmds(t_pipex *pipex, int fd_file_in, int fd_file_out,
				size_t cmd_count)
{
	int		pipe_fds[2];
	int		fds[2];
	size_t	idx;

	idx = 0;
	if (pipe(pipe_fds))
		return (0);
	if (!run_first(pipex, fd_file_in, pipe_fds[OUT]))
		return (0);
	while (++idx < cmd_count - 1)
	{
		fds[IN] = pipe_fds[IN];
		if (pipe(pipe_fds))
			return (0);
		fds[OUT] = pipe_fds[OUT];
		if (!cmd_fork(pipex->envp, pipex->cmds[idx], pipex->args[idx], fds))
			return (0);
		close(fds[IN]);
	}
	return (run_last(pipex, pipe_fds[IN], fd_file_out, cmd_count - 1));
}

int	pipex_run(t_pipex *pipex)
{
	int		fd_in;
	int		fd_out;
	size_t	cmd_count;

	cmd_count = 0;
	while (pipex->cmds[cmd_count])
		cmd_count++;
	fd_in = open(pipex->filein, O_RDONLY);
	if (fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", strerror(errno),
			pipex->filein);
		return (0);
	}
	fd_out = open(pipex->fileout, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", strerror(errno),
			pipex->fileout);
		return (0);
	}
	return (run_cmds(pipex, fd_in, fd_out, cmd_count));
}
