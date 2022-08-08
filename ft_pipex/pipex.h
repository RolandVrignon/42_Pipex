/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:25:22 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/08 13:15:42 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

void	close_pipes(int *fd);

void	child_process(char **av, char **envp, int *fd);

void	parent_process(char **av, char **envp, int *fd);

void	process(char **av, char **envp, int fd[2]);

void	free_double(char **tab);

char	**find_path(char **envp);

char	*find_cmdpath(char *cmd, char **envp);

void	execute(char *av, char **envp, int *fd);

#endif
