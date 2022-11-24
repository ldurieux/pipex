/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:55:05 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:55:06 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_INTERNAL_H
# define PIPEX_INTERNAL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex	t_pipex;

/* replace all cmds in pipex by their path
 * return 0 if a cmd was not found or
 * if execution is denied
*/
int		pipex_sanitize_cmds(t_pipex *pipex, size_t cmd_count);

void	pipex_run_child(char **envp, char *cmd, char *args, int fds[2]);
int		pipex_run_parent(pid_t child_pid, int fd_pipe_write);

int		run_cmds(t_pipex *pipex, int fd_file_in, int fd_file_out,
			size_t cmd_count);

void	*ft_realloc(void **ptr, size_t *size, size_t new_size);

#endif // PIPEX_INTERNAL_H
