/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/18 01:13:47 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *av, char **envp, int *fd)
{
	char	**cmd;
	int		i;
	char	*path;
	char	*err;

	i = -1;
	cmd = ft_split(av, ' ');
	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
		path = find_path(cmd[0], envp);
	if (!path)
	{
		err = ft_strjoin(cmd[0], ": Command not found\n");
		ft_putstr_fd(err, 2);
		free(err);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		close_pipes(fd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
		exit(EXIT_FAILURE);
}
