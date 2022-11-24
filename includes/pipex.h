/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:55:03 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/18 11:55:04 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_pipex
{
	char	**envp;
	char	*filein;
	char	*fileout;
	char	**cmds;
	char	**args;
	char	*here_doc;
}	t_pipex;

t_pipex	*pipex_new(char **envp, int argc, char **args);
void	pipex_delete(t_pipex *pipex);
int		pipex_run(t_pipex *pipex);

#endif // PIPEX_H
