#include "pipex.h"

void	pipex_run(t_pipex *pipex)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(pipex->filein, O_RDONLY);
	fd_out = open(pipex->fileout, O_WRONLY);
	if (fd_in == -1 || fd_out == -1)
		return ;
}