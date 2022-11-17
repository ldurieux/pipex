#ifndef PIPEX_INTERNAL_H
# define PIPEX_INTERNAL_H

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex t_pipex;

/* replace all cmds in pipex by their path
 * return 0 if a cmd was not found or
 * if execution is denied
*/
int		pipex_sanitize_cmds(t_pipex *pipex, size_t cmd_count);

void	pipex_run_child(char **envp, char *cmd, char *args, int fds[2]);
int		pipex_run_parent(pid_t child_pid, int fd_pipe_write);

#endif // PIPEX_INTERNAL_H
