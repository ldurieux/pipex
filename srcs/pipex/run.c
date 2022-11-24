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
#define BUFFER_START_SIZE 64

static int	pipex_run_normal(t_pipex *pipex, size_t cmd_count)
{
	int		fd_in;
	int		fd_out;

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

static char	*read_line_until(char *token, size_t len_token)
{
	char	*buffer;
	size_t	mem_size;
	size_t	buf_size;
	ssize_t	bytes_read;

	buf_size = 0;
	mem_size = BUFFER_START_SIZE;
	buffer = ft_calloc(sizeof(char), BUFFER_START_SIZE);
	if (!buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read(STDIN_FILENO, buffer + buf_size, 1);
		if (bytes_read < 0 || ft_strncmp(buffer, token, len_token) == 0)
			return (free(buffer), NULL);
		buf_size += bytes_read;
		if (bytes_read == 0 || buffer[buf_size - bytes_read] == '\n')
			break ;
		if (buf_size >= mem_size + 2)
			if (!ft_realloc((void **)&buffer, &buf_size, buf_size * 2))
				return (free(buffer), NULL);
	}
	buffer[buf_size] = 0;
	return (buffer);
}

static int	pipex_run_here_doc(t_pipex *pipex, size_t cmd_count)
{
	char	*line;
	int		fds[2];
	int		fd_out;
	size_t	len_here_doc;

	if (pipe(fds))
		return (0);
	fd_out = open(pipex->fileout, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", strerror(errno),
			pipex->fileout);
		return (0);
	}
	len_here_doc = ft_strlen(pipex->here_doc);
	line = read_line_until(pipex->here_doc, len_here_doc);
	while (line)
	{
		ft_putstr_fd(line, fds[OUT]);
		free(line);
		line = read_line_until(pipex->here_doc, len_here_doc);
	}
	close(fds[OUT]);
	return (run_cmds(pipex, fds[IN], fd_out, cmd_count));
}

int	pipex_run(t_pipex *pipex)
{
	size_t	cmd_count;

	cmd_count = 0;
	while (pipex->cmds[cmd_count])
		cmd_count++;
	if (pipex->here_doc)
		return (pipex_run_here_doc(pipex, cmd_count));
	else
		return (pipex_run_normal(pipex, cmd_count));
}
