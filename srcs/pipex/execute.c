#include "pipex.h"

static void	free_strarr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = (size_t)-1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static void	run_child(t_pipex *pipex, char *cmd, char *args)
{
	char	**res_args;
	char	**cmd_args;
	size_t	size;

	//TODO: properly split args
	cmd_args = ft_split(args, ' ');
	if (!cmd_args)
		exit(126);
	size = (size_t)-1;
	while (cmd_args[++size])
		;
	res_args = malloc(sizeof(char *) * (size + 2));
	if (!res_args)
	{
		free_strarr(cmd_args);
		return ;
	}
	res_args[0] = cmd;
	ft_memcpy((void *)(res_args + 1), (void *)cmd_args,
				sizeof(char *) * (size + 1));
	free(cmd_args);
	if (execve(cmd, res_args, pipex->envp) != -1)
	{
		free_strarr(res_args);
		exit(0);
	}
	ft_putendl_fd(cmd, STDOUT_FILENO);
	ft_putendl_fd(res_args[1], STDOUT_FILENO);
	free_strarr(res_args);
	exit(127);
}

static void run_parent(pid_t child_pid)
{
	int	status;

	waitpid(child_pid, &status, WUNTRACED);
}

static void	run(t_pipex *pipex, char *cmd, char *args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		run_child(pipex, cmd, args);
	else if (pid > 0)
		run_parent(pid);
	else
		ft_putendl_fd("fork error\n", STDERR_FILENO);
}

static void	run_filein(t_pipex *pipex, char *cmd, char *args, int filein_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(filein_fd, STDIN_FILENO);
		run_child(pipex, cmd, args);
	}
	else if (pid > 0)
		run_parent(pid);
	else
		ft_putendl_fd("fork error\n", STDERR_FILENO);
}

void	pipex_execute(t_pipex *pipex)
{
	int	filein_fd;

	filein_fd = open(pipex->filein, O_RDONLY);
	if (!filein_fd)
	{
		ft_putstr_fd("pipex: couldn't open file: ", STDERR_FILENO);
		ft_putendl_fd(pipex->filein, STDERR_FILENO);
		return ;
	}
	run_filein(pipex, pipex->cmds[0], pipex->args[0], filein_fd);
}
