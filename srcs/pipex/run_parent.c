#include "pipex_internal.h"
#include "pipex.h"

int	pipex_run_parent(pid_t child_pid, int fd_pipe_write)
{
	int	status;

	close(fd_pipe_write);
	waitpid(child_pid, &status, 0);
	return (status);
}
