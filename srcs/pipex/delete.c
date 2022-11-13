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
	free(pipex);
}
