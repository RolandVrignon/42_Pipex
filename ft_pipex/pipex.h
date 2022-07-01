/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:26:58 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/01 15:05:11 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_pipex {
	int		pid;
	int		infile_fd;
	char	outfile_fd;
	int		cmd_nbr;
	char	*env_path;
	int		*pfd;
	int		pipe_nbr;
	char	**cmd;
	char	**opt;
	char	**cpath;

}	t_pipex;

// ---------- PARSING

char	*get_cmd_path(char *cmd, char *envp_PATH);

char	*get_envp(char **envp);

char	**get_paths(t_pipex pipex);

char	**get_cmd(int cmd_nbr, char **av, int heredoc);

char	**get_opt(int cmd_nbr, char **av, int heredoc);

t_pipex	set_pipex(int ac, char **av, char **envp, int heredoc);

t_pipex	heredoc_stuff(int ac, char **av, int heredoc);

int		free_stuff(t_pipex pipex);

void	free_double(char **tab);

// ----------- PIPEX

int		create_pipes(t_pipex pipex);

void	close_pipes(t_pipex pipex);

void	create_childs(t_pipex pipex, int i, char **envp);

#endif