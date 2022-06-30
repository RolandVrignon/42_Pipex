/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:26:58 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 15:52:13 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"
#include <sys/wait.h>

typedef struct s_pipex {
	// files
	char	*infile;
	char	*outfile;
	// infos
	int		cmd_nbr;
	char	*env_path;
	// pipes
	int		*pfd;
	int		pipe_nbr;
	// commands
	char	**cmd;
	char	**opt;
	char	**cpath;

}	t_pipex;

// ---------- PARSING

char	*get_cmd_path(char *cmd, char *envp_PATH);

char	*get_envp(char **envp);

char	**get_paths(t_pipex pipex);

char	**get_cmd(int cmd_nbr, char **av);

char	**get_opt(int cmd_nbr, char **av);

t_pipex set_pipex(int ac, char **av, char **envp);

int		free_stuff(t_pipex pipex);

void	free_double(char **tab);

// ----------- PIPEX

int		create_pipes(t_pipex pipex);

void	close_pipes(t_pipex pipex);


#endif