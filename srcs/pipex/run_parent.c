/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:54:42 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:54:44 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_internal.h"
#include "pipex.h"

int	pipex_run_parent(pid_t child_pid, int fd_pipe_write)
{
	int	status;

	close(fd_pipe_write);
	waitpid(child_pid, &status, 0);
	return (status);
}
