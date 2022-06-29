/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:26:58 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/29 19:23:39 by rvrignon         ###   ########.fr       */
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

char	*get_cmd_path(char *cmd, char *envp_PATH);

char	*get_envp(char **envp);

int		create_pipes(t_pipex *pipex);

char	**get_paths(t_pipex *pipex, char **cmd, char **envp);

char	**get_cmd(int cmd_nbr, char **av);

char	**get_opt(int cmd_nbr, char **av);

t_pipex *set_pipex(int ac, char **av, char **envp);

int		free_stuff(t_pipex *pipex);

int		main(int ac, char **av, char **envp);


#endif