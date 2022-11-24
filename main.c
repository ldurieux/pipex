/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:55:16 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:55:18 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define MIN_ARGS 5
#define LEN_HERE_DOC 8

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < MIN_ARGS)
	{
		ft_putendl_fd("Usage: {file_in} [commands](2...n) {file_out}.",
			STDERR_FILENO);
		return (1);
	}
	if (argc < (MIN_ARGS + !ft_strncmp(argv[1], "here_doc", LEN_HERE_DOC)))
	{
		ft_putendl_fd("Usage: {file_in} [commands](2...n) {file_out}.",
			STDERR_FILENO);
		return (1);
	}
	pipex = pipex_new(envp, argc - 1, argv + 1);
	if (!pipex)
		return (1);
	pipex_run(pipex);
	pipex_delete(pipex);
	return (0);
}
