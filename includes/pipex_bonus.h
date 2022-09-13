/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:25:22 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/13 16:47:36 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_pipex{
	int		ac;
	char	**av;
	char	**envp;
	int		i;
	pid_t	pid;
	int		fd[2];
	int		oldfd;
	int		heredoc;
}	t_pipex;

void	child_process(t_pipex *pipe);

int		handle_fd(t_pipex *pipex);

void	process(t_pipex *pipe);

int		check_path(char **envp);

t_pipex	*set_pipex(int ac, char **av, char **envp);

void	free_double(char **tab);

char	**find_path(char **envp);

char	*find_cmdpath(char *cmd, char **envp);

void	execute(char *av, char **envp, int *fd);

void	close_pipes(int fd[2]);

void	error(void);

void	print(char *s);

int		last_cmd(t_pipex *pipex);

int		handle_fd(t_pipex *pipex);

int		first_cmd(t_pipex *pipex);

int		heredoc(t_pipex *pipex);

#endif
