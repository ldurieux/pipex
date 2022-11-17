#include "pipex.h"

#define MIN_ARGS 5

int main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < MIN_ARGS)
	{
		ft_putendl_fd("Usage: {file_in} [commands](2...n) {file_out}.", STDERR_FILENO);
		return (1);
	}
	pipex = pipex_new(envp, argc - 1, argv + 1);
	if (!pipex)
		return (1);
	if (!pipex_run(pipex))
		ft_putendl_fd("An error occured.", STDERR_FILENO);
	pipex_delete(pipex);
	return (0);
}
