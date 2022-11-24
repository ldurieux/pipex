/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:54:30 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:54:34 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_delete(t_pipex *pipex)
{
	size_t	i;

	if (!pipex)
		return ;
	if (pipex->cmds)
	{
		i = (size_t) - 1;
		while (pipex->cmds[++i])
			free(pipex->cmds[i]);
		free(pipex->cmds);
	}
	free(pipex->args);
	free(pipex->here_doc);
	free(pipex);
}
