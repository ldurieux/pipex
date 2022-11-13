#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"

typedef struct s_pipex
{
	char	**envp;
	char	*filein;
	char	*fileout;
	char	**cmds;
	char	**args;
}	t_pipex;

t_pipex	*pipex_new(char **envp, int argc, char **args);
void	pipex_delete(t_pipex *pipex);

void	pipex_run(t_pipex *pipex);
void	pipex_execute(t_pipex *pipex);

#endif // PIPEX_H
